# 고급 시스템 프로그래밍 Advanced System Programming

국민대학교 컴퓨터공학부

- 실습을 위한 파일들
- 예제 파일들
 
File

- gen.c   : n 개의  m MB의 크기의 text 파일 만들기 (file merge용)
- merge.c : merge.c 두개의 파일을 merge 하고 시간을 재는 예제 소스 
- chat.c  : chatting을 위한 소스 (아직 준비 안됨)

## 시도

1. gcc -g 옵션 제거(바이너리 파일에 디버깅 정보 삽입하는 옵션)
* gcc merge.c -o merge

2. gcc 컴파일 최적화 옵션 변경
* gcc -O merge.c -o merge
* gcc -O1 merge.c -o merge
* gcc -O2 merge.c -o merge
* gcc -O3 merge.c -o merge
