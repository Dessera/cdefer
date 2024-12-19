# cdefer.h

A simple C library for defer statement.

## Usage

```c
#include <cdefer/cdefer.h>
#include <stdio.h>

int main() {
  DEFER(printf("on exit\n"););

  printf("in function body\n");
}
```

output:

```shell
in function body
on exit
```