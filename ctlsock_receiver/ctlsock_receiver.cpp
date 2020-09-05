#include "ctlsock_receiver.hpp"

#define super IOService
OSDefineMetaClassAndStructors(ctlsock_receiver, IOService)

bool ctlsock_receiver::init(OSDictionary *dict) {
    IOLog("Initializing");
    printf("Initializing LOOOL\n");
    bool result = super::init(dict);
    return result;
}

void ctlsock_receiver::free(void) {
    IOLog("Freeing\n");
    super::free();
}

IOService *ctlsock_receiver::probe(IOService *provider, SInt32 *score) {
    IOService *result = super::probe(provider, score);
    IOLog("Probing\n");
    return result;
}

void ctlsock_receiver::stop(IOService *provider) {
    IOLog("Stopping\n");
    super::stop(provider);
}

errno_t ctlHandleSet(kern_ctl_ref ctlref, unsigned int unit, void *userdata, int opt, void *data, size_t len) {
    errno_t error = KERN_SUCCESS;
    
    IOLog("ctlHandleSet, opt: %d", opt);
    
    return error;
}

errno_t ctlHandleGet(kern_ctl_ref ctlref, unsigned int unit, void *userdata, int opt, void *data, size_t *len) {
    errno_t error = KERN_SUCCESS;
    IOLog("ctlHandleGet, opt: %d", opt);
    return error;
}

errno_t ctlHandleConnect(kern_ctl_ref ctlref, struct sockaddr_ctl *sac, void **unitinfo) {
    errno_t error = KERN_SUCCESS;
    IOLog("ctlHandleConnect. Unit: %d", sac->sc_unit);
    return error;
}
errno_t ctlHandleDisconnect(kern_ctl_ref ctlref, unsigned int unit, void *unitinfo) {
    errno_t error = KERN_SUCCESS;
    IOLog("ctlHandleDisconnect");
    return error;
}

errno_t ctlHandleWrite(kern_ctl_ref ctlref, unsigned int unit, void *userdata, mbuf_t m, int flags) {
    errno_t error = KERN_SUCCESS;
    
    IOLog("ctlHandleHandleWrite");
    
    uint8_t *data = (uint8_t*)mbuf_data(m);
    uint8_t data_bkup[mbuf_len(m)+1];
    memcpy(data_bkup, data, mbuf_len(m));
    data_bkup[mbuf_len(m)] = 0x01;
    
    return error;
}

bool ctlsock_receiver::start(IOService *provider) {
    bool result = super::start(provider);
    IOLog("Starting!! LOOOL\n");
    
    errno_t err;
    bzero(&mCtl, sizeof(mCtl));
    mCtl.ctl_id = 0;
    mCtl.ctl_unit = 0;
    strcpy(mCtl.ctl_name, kThisKextID, strlen(kThisKextID));
    mCtl.ctl_flags = CTL_FLAG_PRIVILEGED;
    mCtl.ctl_send = ctlHandleWrite;
    mCtl.ctl_getopt = ctlHandleGet;
    mCtl.ctl_setopt = ctlHandleSet;
    mCtl.ctl_connect = ctlHandleConnect;
    mCtl.ctl_disconnect = ctlHandleDisconnect;
    err = ctl_register(&mCtl, &mCtlref);
    
    u_int32_t ctl_id = mCtl.ctl_id;
    IOLog("ctl_register status: %d, id: %d", err, ctl_id);
    return result;
}
