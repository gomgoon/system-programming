#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#define DB_FILE "counter.data"  // 매핑할 파일 이름
#define MAGIC "42"              // 마법 숫자로 사용되는 키
#define MAGIC_SIZ sizeof(MAGIC)

struct glob_id {
    char magic[3];  // 마법 문자열 "42\0"
    time_t ts;      // 마지막 수정 타임스탬프
    long val;       // 전역 카운터 값
};

// 마법 숫자 검증 함수
int glob_id_verify_magic(int fd, struct glob_id *id) {
    int rc;
    // 마법 숫자를 확인합니다.
    // 두 값이 같으면 0을 반환합니다.
    rc = strncmp(id->magic, MAGIC, 3);
    return rc;
}

// 전역 ID에 값을 쓰는 함수
void glob_id_write(struct glob_id *id, long val) {
    // 마법 숫자(42)를 id.magic에 복사합니다.
    memcpy(id->magic, MAGIC, MAGIC_SIZ);
    id->ts = time(NULL);  // 현재 시간(초)을 id.ts에 저장합니다.
    id->val = val;        // 카운터 값을 id.val에 복사합니다.
}

