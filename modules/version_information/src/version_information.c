/* *
 *
 * 
 *
 * */

#include "ch.h"
#include "hal.h"
#include "version_information.h"

/*===========================================================================*/
/* Module local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Module exported variables.                                                */
/*===========================================================================*/

/** @brief  Save location for the KFly Version string. */
__attribute__ ((used, section(".sw_version")))
    const char build_version[] = SW_VERSION;

/*===========================================================================*/
/* Module local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

/**
 * @brief               Gets the pointer to the hardware's unique ID.
 *
 * @return              Returns pointer to hardware's unique ID.
 */
const uint8_t *ptrGetUniqueID(void)
{
    return (const uint8_t *)(UNIQUE_ID_BASE);
}

/**
 * @brief               Gets the pointer to the bootloader's version string.
 *
 * @return              Returns pointer to bootloader's version string.
 */
const uint8_t *ptrGetBootloaderVersion(void)
{
    return (const uint8_t *)(BOOTLOADER_BASE + SW_VERSION_OFFSET);
}

/**
 * @brief               Gets the pointer to firmware's version string.
 *
 * @return              Returns pointer to firmware's version string.
 */
const uint8_t *ptrGetFirmwareVersion(void)
{
    return (const uint8_t *)(FIRMWARE_BASE + SW_VERSION_OFFSET);
}
