package main

import (
    "fmt"
)

func main() {
    var s int64 = 0
    for i := 0; i < 10_000_000; i++ {
        s += int64(i)
    }
    fmt.Println("Sum:", s)
}
