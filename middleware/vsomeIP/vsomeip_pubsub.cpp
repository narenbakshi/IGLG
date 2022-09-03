
#include "config.hpp"
#include "vsomeip_pubsub.hpp"

/***********************************************************************************************/

/**
 * @brief Function to bind publish for vsomeipmessage.
 * @param Handlerstruct Handle strucure with all required data.
 * @return int: Returns socket.
 */
void vsmippub_bind(Handlerstruct *me)
{
    std::string newtopic(me->topic);
    me->sockVsomeIPpub = new pubVsomeIP(newtopic);
    me->sockVsomeIPpub->init();
    me->sockVsomeIPpub->start();
}

/**
 * @brief Function to subscribe data with vsomeipmessage.
 * @param Handlerstruct Handle strucure with all required data.
 * @return char: Returns reveived data.
 */
void vsmippublish(Handlerstruct *me, char *data)
{
    std::string s(data);
    me->sockVsomeIPpub->run(s, std::chrono::milliseconds(1));
    
}


/**
 * @brief Function to bind subscribe for vsomeipmessage.
 * @param Handlerstruct Handle strucure with all required data.
 * @return int: Returns socket.
 */
void vsmipsub_bind(Handlerstruct *me)
{
    //subVsomeIP* subVsomeIP;
    std::string newtopic(me->topic);
    me->sockVsomeIPsub = new subVsomeIP(newtopic);
    //subnew->sockVsomeIPsub = subVsomeIP;
    me->sockVsomeIPsub->init();
    me->sockVsomeIPsub->start();
    
}

/**
 * @brief Function to subscribe data with vsomeipmessage.
 * @param Handlerstruct Handle strucure with all required data.
 * @return char: Returns reveived data.
 */
char* vsmipsubscribe(Handlerstruct *me)
{
    me->sockVsomeIPsub->run(std::chrono::seconds(2));

    std::this_thread::sleep_for(std::chrono::seconds(9));
    
}



/**
 * @brief Function to initialize the framework structure. It initializes with all the nanomsg function pointers.
 * @param structframwork Structure for framework.
 * @return void.
 */
void vsmip_operation_initialize(struct framwork *frame)
{
	frame->publish = &vsmippublish;
	frame->subscribe = &vsmipsubscribe;
	frame->pub_bind =  &vsmippub_bind;
	frame->sub_bind = &vsmipsub_bind;
 
}