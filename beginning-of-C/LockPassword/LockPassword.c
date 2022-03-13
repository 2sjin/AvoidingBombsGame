#include <stdio.h>

int main() {

	int i = 1;

	printf("순번\t비밀번호\n");

	for (int pw = 1234; pw <= 56789; pw++) {

		// 각 자릿수의 값 
		int p1 = pw % 100000 / 10000;
		int p2 = pw % 10000 / 1000;
		int p3 = pw % 1000 / 100;
		int p4 = pw % 100 / 10;
		int p5 = pw % 10 / 1;

		if (p1 < p2 && p2 < p3 && p3 < p4 && p4 < p5)
			printf("%03d\t%05d\n", i++, pw);
	}
}