#ifndef __BOOT_DENPENDENT_H
#define __BOOT_DENPENDENT_H

/* 依赖 app 库*/
#include "app.h"
/* Includes ------------------------------------------------------------------*/

/*  移植过来的 */
#define RDP_ENABLE (0) /* 0 = 关闭 其它值开启读取保护（重新编译bootloader）*/
#define G_BUF_SIZE (128*1024)
#define BIN_SFN_U "750VB.BIN"
#define BIN_SFN_L "750vb.bin"

enum
{
    IAP_OK = 0,
    IAP_FS_ERR = -1,
    IAP_ERASE_ERR = -2,
    IAP_WRITE_ERR = -3,
    IAP_VERIFY_ERR = -4
};

struct datetime_st
{
    uint32_t date;
    uint32_t time;
};
#define EE_RW_SIZE sizeof(struct datetime_st)

int find_bin_files(struct datetime_st *d, uint8_t *n, char *DiskPath);
int read_eeprom(struct datetime_st *d);
int iap(const char *path, uint8_t *buf, uint32_t buf_size);
int update_eeprom(struct datetime_st *d);

#endif