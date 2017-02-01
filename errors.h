/*
 * Human errors descriptions
 * matching error codes defined in ph_Status.h
 *
 * usage:
 *  if (handle_error(status, ReadError)) return NULL;
 *  >> returns error description and component
 *
 * OR:
 *  if (handle_error(status, ReadError, "custom message")) return NULL;
 *  >> returns customer error and component
 *
 */


#ifndef NXPPY_ERRORS_H
#define NXPPY_ERRORS_H

#include <ph_Status.h>
#include <phacDiscLoop.h>
#include <Python.h>

char* desc_ph_error(phStatus_t status) {
    switch (status & PH_ERR_MASK) {
    case PH_ERR_IO_TIMEOUT:
        return "IO Timeout, no reply received";
    case PH_ERR_INTEGRITY_ERROR:
        return "Integrity Error, wrong CRC or parity detected";
    case PH_ERR_COLLISION_ERROR:
        return "Collision Error";
    case PH_ERR_BUFFER_OVERFLOW:
        return "Buffer Overflow, attempted to write beyond buffer size";
    case PH_ERR_FRAMING_ERROR:
        return "Framing Error, invalid frame format";
    case PH_ERR_PROTOCOL_ERROR:
        return "Protocol Error, response violated protocol";
    case PH_ERR_AUTH_ERROR:
        return "Authentication Error";
    case PH_ERR_READ_WRITE_ERROR:
        return "Read/Write Error, occured in RAM/ROM or Flash";
    case PH_ERR_TEMPERATURE_ERROR:
        return "Temperature Error, RC sensors detected overheating";
    case PH_ERR_RF_ERROR:
        return "RF Error";
    case PH_ERR_INTERFACE_ERROR:
        return "Interface Error, occured in RC communication";
    case PH_ERR_LENGTH_ERROR:
        return "Length Error";
    case PH_ERR_RESOURCE_ERROR:
        return "Resource Error";
    case PH_ERR_TX_NAK_ERROR:
        return "NAK Error, TX rejected sanely by the counterpart";
    case PH_ERR_RX_NAK_ERROR:
        return "NAK Error, RX request rejected sanely by the counterpart";
    case PH_ERR_EXT_RF_ERROR:
        return "Error due to External RF";
    case PH_ERR_NOISE_ERROR:
        return "EMVCo EMD Noise Error";
    case PH_ERR_ABORTED:
        return "HAL shutdown was called";
    case PH_ERR_INTERNAL_ERROR:
        return "Internal Error";
    case PH_ERR_INVALID_DATA_PARAMS:
        return "Invalid Data Parameters Error, layer ID check failed";
    case PH_ERR_INVALID_PARAMETER:
        return "Parameter Error, invalid parameter supplied";
    case PH_ERR_PARAMETER_OVERFLOW:
        return "Parameter Overflow, reading/writing produced an overflow";
    case PH_ERR_UNSUPPORTED_PARAMETER:
        return "Parameter not supported";
    case PH_ERR_UNSUPPORTED_COMMAND:
        return "Command not supported";
    case PH_ERR_USE_CONDITION:
        return "Condition Error";
    case PH_ERR_KEY:
        return "Key Error";
    case PH_ERR_OSAL_ERROR:
        return "OSAL Error occurred during initialization";
    // from phacDiscloop.h
    case PHAC_DISCLOOP_FAILURE:
        return "Failure due to error from lower layer";
    case PHAC_DISCLOOP_COLLISION_PENDING:
        return "Collision pending";
    case PHAC_DISCLOOP_EXTERNAL_RFON:
        return "External RF field on";
    case PHAC_DISCLOOP_EXTERNAL_RFOFF:
        return "External RF field off";
    case PHAC_DISCLOOP_NO_TECH_DETECTED:
        return "No card/device detected";
    case PHAC_DISCLOOP_NO_DEVICE_RESOLVED:
        return "No card/device resolved";
    case PHAC_DISCLOOP_LPCD_NO_TECH_DETECTED:
        return "LPCD succeeded but no card/device detected";
    case PHAC_DISCLOOP_MULTI_TECH_DETECTED:
        return "Multiple cards/devices detected";
    case PHAC_DISCLOOP_MULTI_DEVICES_RESOLVED:
        return "Multiple cards/devices resolved";
    }

    return "Unknown Error";
}


char* desc_ph_comp(phStatus_t status) {
    switch(status & PH_COMP_MASK) {
    case PH_COMP_GENERIC:
        return "Generic Component";
    case PH_COMP_BAL:
        return "BAL Component";
    case PH_COMP_HAL:
        return "HAL Component";
    case PH_COMP_PAL_ISO14443P3A:
        return "ISO14443-3A PAL-Component";
    case PH_COMP_PAL_ISO14443P4A:
        return "ISO14443-4A PAL-Component";
    case PH_COMP_PAL_MIFARE:
        return "Mifare PAL-Component";
    case PH_COMP_PAL_FELICA:
        return "FeliCa PAL-Component";
    case PH_COMP_PAL_GENERALTARGET:
        return "General Target/Listen mode Component";
    case PH_COMP_AL_MFC:
        return "Mifare Classic AL-Component";
    case PH_COMP_AL_MFUL:
        return "Mifare Ultralight AL-Component";
    case PH_COMP_AL_MFP:
        return "Mifare Plus AL-Component";
    case PH_COMP_AL_VCA:
        return "Virtual Card AL-Component";
    case PH_COMP_AL_FELICA:
        return "Open FeliCa AL-Component";
    case PH_COMP_AL_MFDF:
        return "Mifare DESFIRE EV1 AL-Component";
    case PH_COMP_AL_MFDFEV2:
        return "Mifare DESFIRE EV2 AL-Component";
    case PH_COMP_AL_TOP:
        return "Tag Operation AL-Component";
        case PH_COMP_DL_AMP:
        return "Amplifier DL-Component";
    case PH_COMP_DL_OSCI:
        return "Oscilloscope DL-Component";
    case PH_COMP_DL_RDFPGA:
        return "Reader FPGA Box DL-Component";
    case PH_COMP_DL_MSTAMPOSC:
        return "Master Amplifier Oscilloscope DL-Component";
    case PH_COMP_DL_STEPPER:
        return "Stepper DL-Component";
    case PH_COMP_AC_DISCLOOP:
        return "Discovery Loop Component";
    case PH_COMP_CE_T4T:
        return "Card Emulation T4T Component";
    case PH_COMP_LN_LLCP:
        return "LLCP Component";
    case PH_COMP_NP_SNEP:
        return "SNEP Component";
    case PH_COMP_CIDMANAGER:
        return "Cid Manager Component";
    case PH_COMP_CRYPTOSYM:
        return "CryptoSym Component";
    case PH_COMP_KEYSTORE:
        return "KeyStore Component";
    case PH_COMP_TOOLS:
        return "Tools Component";
    case PH_COMP_CRYPTORNG:
        return "CryptoRng Component";
    case PH_COMP_LOG:
        return "Log Component";
    case PH_COMP_OSAL:
        return "OS AL Component";
    case PH_COMP_PLATFORM:
        return "MicroController Platform Component";
    }

    return "Undefined Component";
}

int handle_error_msg(phStatus_t status, PyObject* errorType, char* message) {
    // No error, alls good
    if (status == PH_ERR_SUCCESS) {
        return false;
    }
    else if (message != NULL) {
        PyErr_Format(errorType, "Nxppy: %d, %s from %s", status, message, desc_ph_comp(status));
        return true;
    }
    else {
        PyErr_Format(errorType, "Nxppy: %s from %s", desc_ph_error(status), desc_ph_comp(status));
        return true;
    }
}

int handle_error(phStatus_t status, PyObject* errorType) {
    return handle_error_msg(status, errorType, NULL);
}

#endif // NXPPY_ERRORS_H
