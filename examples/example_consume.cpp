#include "AMQPcpp.h"

using namespace std;

int i=0;

int onCancel(AMQPMessage * message ) {
    cout << "cancel tag="<< message->getDeliveryTag() << endl;
    return 0;
}

int  onMessage( AMQPMessage * message  ) {
    uint32_t j = 0;
    char * data = message->getMessage(&j);
    if (data)
        cout << data << endl;

    i++;

    cout << "#" << i << " tag="<< message->getDeliveryTag() << " content-type:"<< message->getHeader("Content-type") ;
    cout << " encoding:"<< message->getHeader("Content-encoding")<< " mode="<<message->getHeader("Delivery-mode")<<endl;

    if (i > 5) {
        AMQPQueue * q = message->getQueue();
        q->Cancel( message->getConsumerTag() );
    }
    return 0;
};


int main ()
{
    try {
        AMQP amqp("guest:guest@localhost:5672//");

        AMQPExchange* ex2 = amqp.createExchange();
        ex2->Declare("e","fanout");

        AMQPQueue* qu1 = amqp.createQueue();
        qu1->Declare();
        qu1->Bind("e","");

        AMQPQueue * qu2 = amqp.createQueue("q2");
        qu2->Declare();
        qu2->Bind( "e", "");
        qu2->setConsumerTag("tag_123");
        qu2->addEvent(AMQP_MESSAGE, onMessage );
        qu2->addEvent(AMQP_CANCEL, onCancel );

        qu2->Consume(AMQP_NOACK);//

    } catch (AMQPException& e) {
        std::cout << e.getMessage() << std::endl;
    }

    return 0;
}

