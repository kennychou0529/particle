
#include "cellular_hal.h"
#include "modem/mdm_hal.h"


#define CHECK_SUCCESS(x) { if (!(x)) return -1; }

static CellularCredentials cellularCredentials;

cellular_result_t  cellular_on(void* reserved)
{
    CHECK_SUCCESS(electronMDM.powerOn());
    return 0;
}

cellular_result_t  cellular_init(void* reserved)
{
    //MDMParser::DevStatus devStatus = {};
    //CHECK_SUCCESS(electronMDM.init(&devStatus));
    CHECK_SUCCESS(electronMDM.init());
    return 0;
}

cellular_result_t  cellular_off(void* reserved)
{
    CHECK_SUCCESS(electronMDM.powerOff());
    return 0;
}

cellular_result_t  cellular_register(void* reserved)
{
    //MDMParser::DevStatus netStatus = {};
    //CHECK_SUCCESS(electronMDM.registerNet(&netStatus, (system_tick_t) 300000);
    CHECK_SUCCESS(electronMDM.registerNet());
    return 0;
}

cellular_result_t  cellular_pdp_activate(CellularCredentials* connect, void* reserved)
{
    if (strcmp(connect->apn,"") != 0) {
        CHECK_SUCCESS(electronMDM.pdp(connect->apn));
    }
    else {
        CHECK_SUCCESS(electronMDM.pdp());
    }
    return 0;
}

cellular_result_t  cellular_pdp_deactivate(void* reserved)
{
    CHECK_SUCCESS(electronMDM.disconnect());
    return 0;
}

cellular_result_t  cellular_gprs_attach(CellularCredentials* connect, void* reserved)
{
    if (strcmp(connect->apn,"") != 0 || strcmp(connect->username,"") != 0 || strcmp(connect->password,"") != 0 ) {
        CHECK_SUCCESS(electronMDM.join(connect->apn, connect->username, connect->password));
    }
    else {
        CHECK_SUCCESS(electronMDM.join());
    }
    return 0;
}

cellular_result_t  cellular_gprs_detach(void* reserved)
{
    CHECK_SUCCESS(electronMDM.detach());
    return 0;
}

cellular_result_t cellular_device_info(CellularDevice* device, void* reserved)
{
    const MDMParser::DevStatus* status = electronMDM.getDevStatus();
    if (!*status->ccid)
        electronMDM.init(); // attempt to fetch the info again in case the SIM card has been inserted.
    // this would benefit from an unsolicited event to call electronMDM.init() automatically on sim card insert)
    strncpy(device->imei, status->imei, sizeof(device->imei));
    strncpy(device->iccid, status->ccid, sizeof(device->iccid));
    return 0;
}

cellular_result_t cellular_fetch_ipconfig(WLanConfig* config, void* reserved)
{
    memset(&config, 0, sizeof(config));
    return 0;
}

cellular_result_t cellular_credentials_set(const char* apn, const char* username, const char* password, void* reserved)
{
    cellularCredentials.apn = apn;
    cellularCredentials.username = username;
    cellularCredentials.password = password;
    return 0;
}

// todo - better to have the caller pass CellularCredentials and copy the details out according to the size of the struct given.
CellularCredentials* cellular_credentials_get(void* reserved)
{
    return &cellularCredentials;
}

bool cellular_sim_ready(void* reserved)
{
    const MDMParser::DevStatus* status = electronMDM.getDevStatus();
    return status->sim == MDMParser::SIM_READY;
}

// Todo rename me, and allow the different connect, disconnect etc. timeouts be set by the HAL
uint32_t HAL_WLAN_SetNetWatchDog(uint32_t timeOutInuS)
{
    return 0;
}

void cellular_cancel(bool cancel, bool calledFromISR, void*)
{
    if (cancel) {
        electronMDM.cancel();
    } else {
        electronMDM.resume();
    }
}
