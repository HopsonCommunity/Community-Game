# Code Style

## Naming conventions

* File names: PascalCase
* Folder names: underscore_lower_case

* Class names: PascalCase
* Struct names: PascalCase
* Class members: m_camelCase

* Functions: camelCase
* Local variables: camelCase

* Namespaces: PascalCase

* Constants: SCREAMING_SNAKE_CASE

## Class Style

```C++
class Foo
{
    public:
        Foo();
    
        void foo();
        void bar();
        
    protected:
        void barFoo();
        
    private:
        void fooBar();
        
        int m_number;
};
```

* public functions and members at top, protected in middle, private at bottom
* Notice a space between the final class member/function and the next accessor!
* Private members must be prefixed with "_m"

* Initilzation lists:

```C++
Foo::Foo(int x, int y)
:   m_x (x)
,   m_y (y) { }
```

## Namespaces

* NO `using namespace std;` Your pull request will be denied if that is included.
* Namespaces should be PascalCase
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
## Includes
* All headers should have header guards (#pragma once)

* Includes in files should be in the following order:
* "h file corresponding to this cpp file (if applicable)",
* "headers from the same component",
* "headers from other components",
* "headers from SFML"
* "system headers and standard lib headers"

* Example:
```
#include "System.h"

#include "../component/Components.h"
#include "../Entity.h"

#include "../../maths/MathFunctions.h"
#include "../../util/json.hpp"

#include <SFML/Graphics.hpp>

#include <vector>
#include <unordered_map>
```

## Constants
* Do not use C-Style "defines" for constants.
* Use constexpr! It is compile-time determined just like #define is, no excuses!
* Functions can be marked as "constexpr" as well.

## Functions

* Primitives can be passed by value, or reference
* Objects pass as either const reference (or reference), and NEVER BY VALUE
* Indent style:

```C++
bool functionName(int arg1, const std::string& arg2)
{
    if (arg1 > 5)
    {
        std::cout << arg2 << "\n";
        return true;
    }
    return false;
}
```

* For setter functions, use R-Value references and move scematics eg

```C++
void Foo:setString(std::string&& str)
{
    m_string = std::move(str);
}
```

## Slash

* Don't use the `\`, it can cause errors on Linux. Correct use:
```C++
#include <SFML/Graphics.hpp>
```

* This goes for strings as file paths too!

```C++
    std::string filePath = "forward/slashes/so/it/works/cross/platform.png"
```
    
## Pointers

* Please prefer unique pointers to raw owning pointers
```C++
int* x = new int(5); //No!
auto y = std::make_unique<int>(5) //Yes!
```

* If you have to use "new", then you are probably doing something wrong.
* Only case raw pointers are fine is if they are a pointer to a variable (So a non-owning pointer)
* Class members pointers must have a "mp_" prefix

## Enums

* Use enum class, not regular enums!
