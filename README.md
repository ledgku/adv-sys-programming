# 고급 시스템 프로그래밍 Advanced System Programming

국민대학교 컴퓨터공학부

- 실습을 위한 파일들
- 예제 파일들
 
File

- gen.c   : n 개의  m MB의 크기의 text 파일 만들기 (file merge용)
- merge.c : merge.c 두개의 파일을 merge 하고 시간을 재는 예제 소스 
- chat.c  : chatting을 위한 소스 (아직 준비 안됨)

## 시도

### gcc -g 옵션 제거(바이너리 파일에 디버깅 정보 삽입하는 옵션)
- gcc merge.c -o merge

### gcc 컴파일 최적화 옵션 변경
- gcc -O merge.c -o merge
- gcc -O1 merge.c -o merge
- gcc -O2 merge.c -o merge
- gcc -O3 merge.c -o merge

### fputc에서 fputs로 변경
: 매 글자마다 fgetc() 후 fputc() 하는 방법에서 한 라인을 배열에 저장하고 fputs() 하는 방법으로 변경


### 입력 파일 크기의 버퍼를 동적할당하고 fread로 전체를 읽은 후 strtok_r로 라인 단위 파싱해서 fwrite로 쓰기
