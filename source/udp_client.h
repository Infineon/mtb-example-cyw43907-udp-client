/******************************************************************************
* File Name:   udp_client.h
*
* Description: This file contains network configuration parameters related to
*              UDP client operation.
*
*******************************************************************************
* $ Copyright 2021-2023 Cypress Semiconductor $
*******************************************************************************/

#ifndef UDP_CLIENT_H_
#define UDP_CLIENT_H_

/*******************************************************************************
* Macros
********************************************************************************/
/* Wi-Fi Credentials: Modify WIFI_SSID, WIFI_PASSWORD and WIFI_SECURITY_TYPE
 * to match your Wi-Fi network credentials.
 * Note: Maximum length of the Wi-Fi SSID and password is set to
 * CY_WCM_MAX_SSID_LEN and CY_WCM_MAX_PASSPHRASE_LEN as defined in cy_wcm.h file.
 */

#define WIFI_SSID                         "MY_WIFI_SSID"
#define WIFI_PASSWORD                     "MY_WIFI_PASSWORD"

/* Security type of the Wi-Fi access point. See 'cy_wcm_security_t' structure
 * in "cy_wcm.h" for more details.
 */
#define WIFI_SECURITY_TYPE                 CY_WCM_SECURITY_WPA2_AES_PSK

/* Maximum number of connection retries to the Wi-Fi network. */
#define MAX_WIFI_CONN_RETRIES             (10u)

/* Wi-Fi re-connection time interval in milliseconds */
#define WIFI_CONN_RETRY_INTERVAL_MSEC     (1000)

#define MAKE_IPV4_ADDRESS(a, b, c, d)     ((((uint32_t) d) << 24) | \
                                          (((uint32_t) c) << 16) | \
                                          (((uint32_t) b) << 8) |\
                                          ((uint32_t) a))

/* Change the server IP address to match the UDP server address (IP address
 * of the PC).
 */
#define UDP_SERVER_IP_ADDRESS             MAKE_IPV4_ADDRESS(192, 168, 1, 107)
#define UDP_SERVER_PORT                   (50007)

/*******************************************************************************
* Function Prototype
********************************************************************************/
void udp_client_task(void *arg);

#endif /* UDP_CLIENT_H_ */

/* [] END OF FILE */
