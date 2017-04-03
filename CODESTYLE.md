# Code Style

## Namespaces

* NO `using namespace std;` Your pull request will be denied if that is included.
* Namespaces should be CamelCase
* Nested namespaces: 

```C++
namespace Foo {
namespace Bar 
{
    void codeGoesHere()
    {
      
    }
}}
```


* Class, Struct and Namespace names must be uppercased and have camel-casing
* Variable names must be lowercased and have camel-casing
* Private member variables must be prefixed with a `m_`
* Constexpr must be capitalized as if they are defines e.g
```C++
constexpr int FOO_FUNCTION(){ return 0; }
```
* Function names must be lower cased and have camel-casing
* Try to keep code lines no longer than 80 to 100 characters but it is not strongly enforced
* Template variable names should be less than 5 characters in length
* Indenting format:
```C++
class ClassName
{
  public:
    ClassName();
    ...

  private:
    ...
};
```
* Don't use the `\`, it can cause errors on Linux. Correct use:
```C++
#include <SFML/Graphics.hpp>
```

Please prefer unique pointers to raw owning pointers
```C++
int* x = new int(5); //No!
auto y = std::make_unique<int>(5) //Yes!
```
