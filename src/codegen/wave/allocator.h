#include <memory>
#include <vector>

namespace wave::internal
{
   class Allocator
   {
        uint8_t reg = 0;
   public:
        Allocator();
        virtual ~Allocator() = default;
        uint8_t alloc() { return reg++; };
   };
   
}