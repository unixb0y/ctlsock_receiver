#include <sys/kernel_types.h>
#include <sys/kern_control.h>
#include <IOKit/IOService.h>
#include <IOKit/IOLib.h>

//extern mach_port_t      mach_task_self_;
//#define mach_task_self() mach_task_self_
#define kThisKextID "com.unixb0y.ctlsock_receiver"

struct ClientInfo {
    u_int32_t sc_unit = 0;
    bool connected = false;
};

class ctlsock_receiver: public IOService {
    OSDeclareDefaultStructors(ctlsock_receiver)
    public:
        virtual bool init(OSDictionary *dictionary = 0) override;
        virtual void free(void) override;
        virtual IOService *probe(IOService *provider, SInt32 *score) override;
        virtual bool start(IOService *provider) override;
        virtual void stop(IOService *provider) override;
    protected:
        kern_ctl_reg mCtl;
        kern_ctl_ref mCtlref;
        ClientInfo mClient;
        static ctlsock_receiver *mInstance;
};
