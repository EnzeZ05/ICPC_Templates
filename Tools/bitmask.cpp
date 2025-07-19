int _dlg(int x){ //去掉最后一位
	return x >> 1;
}

int __alz(int x){ //在最后加个0
	return x << 1;
}

int __ado(int x){ //在最后加个1
	return x << 1 | 1;
}

int __clo(int x){ //把最后一位变1
	return x | 1;
}

int __clz(int x){ //最后一位变成0
	return x & -2;
}

int __rkto(int x, int k){ //右数第k位变1
	return x | (1 << (k - 1));
}

int __rktz(int x, int k){ //右数第k位变0
	return x & ~(1 << (k - 1));
}

int __rknv(int x, int k){ //右数第k位取反
	return x ^ (1 << (k - 1));
}

int __glt(int x){ //取末3位
	return x & 7;
}

int __glk(int x, int k){ //取末k位
	return x & (1 << k - 1);
}

int __ckto(int x, int k){ //把末尾k位变成1
	return x | ((1 << k) - 1);
}

int __ikiv(int x, int k){ //末尾第k位取反
	return x ^ (1 << k - 1);
}

int __rcoz(int x){ //右边连续的1变0
	return x & (x + 1);
}

int __rfto(int x){ //右边第一个0变1
	return x | (x + 1);
}

int _rcto(int x){ //右边连续的0变成1
	return x | (x - 1);
}

int __gco(int x){ //取右边连续的1
	return (x ^ (x + 1)) >> 1;
}

int __lb(int x){ //去掉右边起第一个1的左边
	return x & -x;
}

/*
&	与	两个位都为1时，结果才为1
|	或	两个位都为0时，结果才为0
^	异或	两个位相同为0，相异为1
~	取反	0变1，1变0
<<	左移	各二进位全部左移若干位，高位丢弃，低位补0
>>	右移	各二进位全部右移若干位，对无符号数，高位补0，有符号数，各编译器处理方法不一样，有的补符号位（算术右移），有的补0（逻辑右移）

c 插入 A ：A |= (1 << c)
A 删除 c ：A &= ~(1 << c)
A 置空 ：A = 0
并集 ：A | B
交集 ：A & B
全集 ：(1 << n) - 1
补集 ：((1 << n) - 1) ^ A
子集 ：(A & B) == B
判断是否是 2 的幂 ：A & (A - 1) == 0
最低位的 1 变为 0 ：n &= (n - 1)
最低位的 1：A & (-A)，最低位的 1 一般记为 lowbit(A)，表示 A 的二进制表达式中最低位的 1 所对应的值。
最低位的 1：A & (-A)，最低位的 1 一般记为 lowbit(A)，表示 A 的二进制表达式中最低位的 1 所对应的值。
最高位的 1：

从子集转移： f[mask] += f[mask ^ (1 << i)];

int p = lowbit(A)
while(p != A){
    A -= p;
    p = lowbit(A);
}
return p;

枚举 A 的子集：
for(subset = (A - 1) & A; subset != A; subset = (subset - 1) & A){
    ...
}

for(i = 0; i <= (1 << n) - 1; ++i){
    ...
}

for(int i = 0; i < (1 << n); i++)
   for(int j = i; ; j = i & (j -  1)) { //这样就可以枚举完i的所有属于它的状态j
      枚举叠加状态: f[i ^ j] //将i ^ j 和  j两组并为1组 i，换句话说就是以当前i的状态，从没有j的状态转移过来
	 //这也就等同于合并 i ^ j 和 j
      if(j == 0) break;
   }
}


#2 滚动数组
有时候状态压缩需要的空间可能会超出限制，滚动数组很好地防止此类情况
如斐波那契数列:
f[i] = f[i - 1] + f[i - 2];

因为递推方程只依赖于f[i - 1] 和 f[i - 2]
所有为了节省空间，滚动数组可大范围做出优化：
f[i % 3] = f[(i - 1) % 3] + f[(i - 2) % 3]
或
int sum = a + b; a = b; b = sum;

同样的二维dp只依赖于 f[i - 1, j], f[i, j - 1]
f[i % 2, j] = f[(i - 1) % 2, j] + f[i % 2, j - 1]

a + b = (a ^ b) + 2 * (a & b) 
*/