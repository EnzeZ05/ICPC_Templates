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