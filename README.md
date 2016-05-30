# TextureProblem

假设 1：印刷机对背景和前景的印刷可以在某一时刻停下来，过一段时间后可继续进行；

如果假设 1 成立，处理流程为：

```
t1  (B, 45) (Y, 10)
t2  (G, 10) (B, 20) (Y, 34)
t3  (Y, 28) (B, 12) (G, 17)
                3/3: 10

t1  (B, 35) (Y, 10)
t2  (B, 20) (Y, 34)
t3  (Y, 18) (B, 12) (G, 17)
                2/3: 18

t1  (B, 35) (Y, 10)
t2  (B, 02) (Y, 34)
t3  (B, 12) (G, 17)
                1/3: 2

t1  (B, 35) (Y, 10)
t2  (Y, 34)
t3  (B, 12) (G, 17)
                2/3: 12

t1  (B, 35) (Y, 10)
t2  (Y, 22)
t3  (G, 17)
                3/3: 17

t1  (B, 18) (Y, 10)
t2  (Y, 05)
t3
                2/2: 5

t1  (B, 13) (Y, 10)
t2
t3
                1/1: 23

** Used 87 minutes. **
```

如果假设 1 不成立：

... TODO
