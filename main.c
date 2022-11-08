#include <inttypes.h>
#include <stdio.h>

#define ONEMILL 1000000

typedef struct bigint{
	int arr[10000];
	int sz;
}bigint;

void sumbig(bigint *b1, bigint* b2, bigint *res) {
	
	if (b1->sz > b2->sz) {
		//swap
		bigint *temp = b1; 
		b1 = b2;
		b2 = temp;
	}

	int i;
	int rem = 0, v;
	for (i = 0; i < b1->sz; i++) {
		v = b1->arr[i] + b2->arr[i] + rem;
		if (v >= ONEMILL) {
			res->arr[i] = v % ONEMILL;
			rem = v / ONEMILL;
		}
		else {
			res->arr[i] = v;
			rem = 0;
		}
	}

	for (; i < b2->sz; i++) {
		v = b2->arr[i] + rem;
		if (v >= ONEMILL) {
			res->arr[i] = v % ONEMILL;
			rem = v / ONEMILL;
		}
		else {
			res->arr[i] = v;
			rem = 0;
		}
	}

	for (; rem >= ONEMILL; i++) {
		res->arr[i] = rem % ONEMILL;
		rem /= ONEMILL;
	}

	if (rem)
		res->arr[i++] = rem;

	res->sz = i;
}

void multipbig(bigint *b1, int64_t f, bigint *res) {
	int rem = 0, i;
	uint64_t v;
	for (i = 0; i < b1->sz; i++) {
		v = b1->arr[i] * f + rem;
		if (v >= ONEMILL) {
			res->arr[i] = v % ONEMILL;
			rem = v / ONEMILL;
		}
		else {
			res->arr[i] = v;
			rem = 0;
		}
	}
	while (rem >= ONEMILL) {
		res->arr[i++] = rem % ONEMILL;
		rem /= ONEMILL;
	}

	if(rem)
		res->arr[i++] = rem;

	res->sz = i;
}

bigint bufbig[4];

int aarr[30005];
void init() {
	aarr[0] = 2;
	for (int i = 1, k = 2; i <= 30000; i+=3, k+=2) {
		aarr[i] = 1;
		aarr[i + 1] = k;
		aarr[i + 2] = 1;
	}
}

int sumdig(bigint *b) {
	int sum = 0, v;
	for (int i = 0; i < b->sz; i++) {
		v = b->arr[i];
		while (v > 9) {
			sum += v % 10;
			v /= 10;
		}
		sum += v;
	}

	return sum;
}

void printbig(bigint* b) {
	for (int i = b->sz - 1; i >= 0; i--) {
		printf("%d", b->arr[i]);
	}
	puts("");
}

int main()
{
	init();

	int n;
	scanf("%d", &n);
	if (n == 1) {
		puts("2");
		return 0;
	}

	int a = 1;
	bigint *pn = bufbig, *pn1 = bufbig + 1, *pn2 = bufbig + 2, *pn1a = bufbig + 3, *temp;
	pn1->arr[0] = aarr[0]; //p0
	pn1->sz = 1;
	pn->arr[0] = aarr[0]* aarr[1] + 1; //p1
	pn->sz = 1;


	for (int i = 2; i < n; i++) {
		//rotate buffers
		temp = pn2;	pn2 = pn1; 	pn1 = pn; 	pn = temp;

		multipbig(pn1, aarr[i], pn1a);
		sumbig(pn2, pn1a, pn);
	}

	int sol = sumdig(pn);

	printf("%d\n", sol);

	return 0;
}
