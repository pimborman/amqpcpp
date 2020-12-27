#include "AMQPcpp.h"

using namespace std;

int main (int argc, char** argv) {



    try {
        //		AMQP amqp;
        //		AMQP amqp(AMQPDEBUG);

        AMQP amqp("guest:guest@localhost:5672//");		// all connect string

        AMQPExchange * ex = amqp.createExchange("e");
        ex->Declare("e", "fanout");

        //AMQPQueue * qu2 = amqp.createQueue("q2");
        //qu2->Declare();
        //qu2->Bind( "e", "");

        ex->setHeader("Delivery-mode", 2);
        ex->setHeader("Content-type", "text/text");
        ex->setHeader("Content-encoding", "UTF-8");

        string ss = "message 1 ";
        // test very long message
        /*
        ss = ss+ss+ss+ss+ss+ss+ss;
        ss += ss+ss+ss+ss+ss+ss+ss;
        ss += ss+ss+ss+ss+ss+ss+ss;
        ss += ss+ss+ss+ss+ss+ss+ss;
        ss += ss+ss+ss+ss+ss+ss+ss;
        */
        ex->Publish(ss ,"");
        //ex->Publish("the following messag is empty","");
        //ex->Publish("","");

        if (argc==2) {
            AMQPQueue * qu = amqp.createQueue();
            qu->Cancel(   amqp_cstring_bytes(argv[1]) );
        }

    } catch (AMQPException e) {
        std::cout << e.getMessage() << std::endl;
    }

    return 0;

}
