#include <ds18b20/sensor.hpp>
#include <ds18b20/sync_wait.hpp>

/** 
   This demo shows how to read the temperature using a synchronous
   approach.

   Note: It's unlikely that the usage of blocking calls is a better
   choice than an asynchronous solution in real projects.

   It's considered that there is only one device using the bus and the
   device has the default resolution of 12bits and the user is
   interested in reading only the whole part of the temperature
   value.
*/

using namespace ds18b20;

void do_something(uint8_t){}

int main() {
    using thermo = sensor<PB3>;

    while(true) {
        auto temp = sync_wait(thermo::read());
        if(temp.has_value())
            do_something(temp.value());
    }
}

