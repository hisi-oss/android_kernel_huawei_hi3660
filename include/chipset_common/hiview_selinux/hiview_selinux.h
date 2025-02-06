#ifndef __HIVIEW_SELINUX_H__
#define __HIVIEW_SELINUX_H__
#include <linux/lsm_audit.h>

#define CONFIG_HUAWEI_HIVIEW_SELINUX
// #define CONFIG_HUAWEI_HIVIEW_SELINUX_PERFORMANCE

int hw_hiview_selinux_avc_audit(struct common_audit_data *cad);

#endif // __HIVIEW_SELINUX_H__
