/*      下面全为 移植所需文件         */
#include "boot_dependent.h"

int read_eeprom(struct datetime_st *d)
{
    uint8_t buf[EE_RW_SIZE];
    struct datetime_st *p = (void *)buf;

    /* Read from I2C EEPROM from 0 */
    BSP_EEPROM_ReadBytes(buf, 0, EE_RW_SIZE);

    d->date = p->date;
    d->time = p->time;

    return 0;
}

int find_bin_files(struct datetime_st *d, uint8_t *n, char *DiskPath)
{
    DIR dir;
    FILINFO fi;
    int ret;

    ret = IAP_OK;
    *n = 0;
    memset(&dir, 0, sizeof(DIR));
    memset(&fi, 0, sizeof(FILINFO));

    /* 打开根目录 */
    if (f_opendir(&dir, DiskPath) != FR_OK)
    {
        ret = IAP_FS_ERR;
        return ret;
    }

    /* Read item from card */
    for (;;)
    {
        if (f_readdir(&dir, &fi) != FR_OK)
        {
            ret = IAP_FS_ERR;
            break;
        }
        if (fi.fname[0] == 0)
        {
            /* 目录搜索完毕正常退出 */
            break;
        }
        else if (fi.fname[0] == '.')
        {
            /* 跳过点目录 */
            continue;
        }

        /* Check for folder or file */
        if (fi.fattrib & AM_DIR)
        {
            /* 忽略目录 */
        }
        else
        {
            if (strcmp(fi.fname, BIN_SFN_U) == 0 || strcmp(fi.fname, BIN_SFN_L) == 0)
            {
                d->date = fi.fdate;
                d->time = fi.ftime;
                *n = ~0;
            }
        }
    }

    /* Close directory */
    f_closedir(&dir);
    return ret;
}

int iap(const char *path, uint8_t *buf, uint32_t buf_size)
{
    uint32_t i;
    uint32_t Address;
    UINT n;
    FRESULT fr;
    FIL f0;
    int ret;

    ret = IAP_OK;

    /* 打开文件 */
    memset(&f0, 0, sizeof(FIL));
    fr = f_open(&f0, path, FA_READ);
    if (fr != FR_OK)
    {
        ret = IAP_FS_ERR;
        return ret;
    }
    
    BSP_LedOn(LED_PLAY_FLAG);
    BSP_LedOn(LED_PSD_FLAG);
    BSP_LedOn(LED_PCM_FLAG);
    /* 擦除扇区 128KB * 3  如果APP大于 128 * 3， 可以增加*/
    if (bsp_EraseCpuFlash(ADDR_FLASH_SECTOR_2_BANK1) != HAL_OK)
    {
        ret = IAP_ERASE_ERR;
        goto iap_quit;
    }
    if (bsp_EraseCpuFlash(ADDR_FLASH_SECTOR_3_BANK1) != HAL_OK)
    {
        ret = IAP_ERASE_ERR;
        goto iap_quit;
    }
    if (bsp_EraseCpuFlash(ADDR_FLASH_SECTOR_4_BANK1) != HAL_OK)
    {
        ret = IAP_ERASE_ERR;
        goto iap_quit;
    }

    /* Program the user Flash area word by word (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) */
    /* 开始写入 */

    BSP_LedOff(LED_PLAY_FLAG);
    BSP_LedOff(LED_PSD_FLAG);
    BSP_LedOff(LED_PCM_FLAG);
    Address = ADDR_FLASH_SECTOR_2_BANK1;
    uint8_t end_Flag = 0;
    while (end_Flag == 0)
    {
        /* 读取文件 */
        if ((fr = f_read(&f0, buf, buf_size, &n)) != FR_OK)
        {
            ret = IAP_FS_ERR;
            goto iap_quit;
        }

        if(n == buf_size)
        {

        }
        else if(n < buf_size)
        {
            /* 填0xff */
            for (i = n; i < buf_size; i++)
            {
                buf[i] = 0xff;
            }
            end_Flag = 1;
        }

        if (n != 0)
        {
            if (bsp_WriteCpuFlash(Address, buf, buf_size) == 0)
            {
            }
            else
            {
                ret = IAP_FS_ERR;
                goto iap_quit;
            }
        }
        Address = Address + CPU_FLASH_SECTOR_SIZE;
    }
    BSP_LedOn(LED_PLAY_FLAG);
    BSP_LedOn(LED_PSD_FLAG);
    BSP_LedOn(LED_PCM_FLAG);
iap_quit:
    /* Lock the Flash to disable the flash control register access (recommended
	to protect the FLASH memory against possible unwanted operation) */
    f_close(&f0);

    return ret;
}

int update_eeprom(struct datetime_st *d)
{
    uint8_t buf[EE_RW_SIZE];
    struct datetime_st *p = (void *)buf;

    p->date = d->date;
    p->time = d->time;

    /* Write on I2C EEPROM from 0 */
    BSP_EEPROM_WriteBytes(buf, 0, EE_RW_SIZE);

    return 0;
}
