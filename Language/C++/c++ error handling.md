## c++ error handling

#### 문자열 -> char && using atoi

```
#include <cstdlib>
#include <vector>
#include <iostream>

using namespace std;

bool solution(string s) {
    bool answer = false;
    char *cast;
    cast=(char*)s.c_str();
    
    if(s.length() == 4 || s.length() == 6){
        if(atoi(cast) != 0)
            answer = true;
        return answer;
    }
    
    return answer;
}
```



