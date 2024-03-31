#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define MAX_PROBABILITY 100.0f              // 성공확률 최대치
#define WAIT_TIME 2                         // 강화 대기시간
#define INITIAL_MONEY 1000000            // 초기 재화
#define BASE_ENHANCEMENT_COST 1000         // 초기 강화 비용
#define ENHANCEMENT_COST_INCREASE 500      // 강화 비용 증가량
#define REVIEW_TICKET_COST 200000          // 복습권 가격

// 강화 등급에 따른 대사 배열
char* enhancementMessages[] = {
    "병아리 신입생(세상의 때가 묻지 않은 귀여운 신입생이 등장했다!)",
    "C언어를 배운 1학년(김영철 교수님께 칭찬을 받은 귀여운 1학년이다.)",
    "HTML5를 배운 1학년(이윤임 교수님의 사랑을 받는 1학년이다.)",
    "포토샵을 배운 1학년(노은석 교수님께서 매우 만족하신다.)",
    "파이썬을 배운 1학년(이은석 교수님께 욕을 많이 먹었다. 슬슬 사람이 이상해진다.)",
    "JavaScript를 배운 1학년(이윤임 교수님께선 큰 신뢰를 걸고 계신다.)",
    "C언어응용을 배운 1학년(김영철 교수님께 혼났다. 분명 C언어를 배웠는데...??)",
    "유니티를 배운 2학년(이성현 교수님께서 걱정하신다. 원래 착했던 애가 이상해지고 있다...)",
    "C# 프로그래밍을 배운 2학년(윤수미 교수님께서 좋아하신다. 다행히 아직 초반이라...)",
    "앱기획을 배운 2학년(김영철 교수님께 맞기 직전까지 갔다. 한강물의 온도가 궁금하다...)",
    "현타가 온 대학생(교수님께 혼나고, 과제에 치이고... 학생의 눈앞에 눈물이 글썽인다.)",
    "반응형웹을 배운 2학년(이은석 교수님께서 좋아하신다. 잠을 자지 않고 과제를 끝냈다.)",
    "C++을 배운 2학년(이제 C계얼 언어를 다 배웠다. 근데 포인터는 도저히 이해가 안된다...)",
    "유니티로 게임을 개발한 3학년(코피를 흘려가며 게임을 만들었다. 이성현 교수님께서 \"이게 게임이 맞나\"라고 하셨다.)",
    "HTML과 CSS로 웹을 만들어 본 3학년(이윤임 교수님께 잔소리를 많이 들었다. 그래도 내심 교수님께서 기특해하신다.)",
    "전공동아리 멘토를 하는 3학년(후배들의 존경을 받고 있다. 이은석 교수님과 이성현 교수님도 그렇게 생각하실까?)",
    "3D모델링을 배운 3학년(노은석 교수님과 1대1 면담을 했다. 아트도 괜찮은 것 같은데... 어디로 갈지 모르겠다.)",
    "창업동아리를 하는 3학년(매일 학교에 21시까지 후배, 동기들과 같이 작업을 한다. 이정도면 귀신이다.)",
    "기획서 작성을 마스터한 3학년(본인은 정말 잘한다고 생각한다. 이은석 교수님과 이성현 교수님도 그렇게 생각하실까?)",
    "현장 실습을 다녀온 3학년(회사에선 오랜만에 인재가 들어왔다고 한다. 하지만 본인은 회사가 별로다.)",
    "졸업 가운을 입고 있는 대학생(모든 능력을 탑재했다. 이제 진짜 지옥을 향해 걸어간다.)"
};

int main(void)
{
    int isTry = 0;                          // 강화를 할 것인지 선택
    int level = 0;                          // 현재 학생의 레벨
    int money = INITIAL_MONEY;              // 현재 학생의 재화
    int reviewTickets = 0;                  // 현재 보유한 복습권 개수
    float probability = MAX_PROBABILITY;    // 현재 학습 성공확률
    int enhancementCost = BASE_ENHANCEMENT_COST; // 현재 강화 비용
    time_t retTime = 0;                     // 대기시간 임시저장 변수
    int randNum = 0;                        // 랜덤값을 저장할 변수

    srand((int)time(NULL));                 // 랜덤 시드값 설정

    while (1)
    {
        // 화면 정리
        system("@cls||clear");

        // 타이틀 화면 출력
        printf(" ** 이지호 학생 키우기 **  \n\n");

        // 현재 상태와 강화 도전 질의 출력
        printf("학생 레벨 : + %d %s\n", level, enhancementMessages[level]);
        printf("학습 성공확률 : %.2f%%\n", probability);
        printf("학생 재화 : %d\n", money);
        printf("복습권 : %d개\n", reviewTickets); // 복습권 개수 출력
        printf("1. 학생 강화 비용 : %d\n", enhancementCost); // 학생 강화 비용 출력
        printf("2. 학생 판매 : %d\n", (level > 0) ? enhancementCost : 0); // 학생 판매 비용 출력
        printf("도전 하시겠습니까?\n\n");
        printf("1.학습   2.포기   3.사교육(상점)\n\n");
        scanf_s("%d", &isTry);

        switch (isTry)
        {
        case 1: // 학습에 도전 할 경우
            if (level < 20) { // 레벨이 20 이상이 아닌 경우에만 강화를 시도하도록 조건 추가
                printf("\n학습중..\n\n");

                // 지정된 시간(초) 만큼 대기
                retTime = time(0) + WAIT_TIME;
                while (time(0) < retTime);

                // 랜덤 값 추출
                randNum = rand() % 100;

                // 재화가 강화 비용보다 작으면 강화를 실행하지 않음
                if (money < enhancementCost) {
                    printf("재화가 부족하여 강화를 할 수 없습니다.\n");
                }
                else {
                    // 추출한 랜덤 값이 성공확률 보다 작으면 성공
                    if (randNum < probability) {
                        // 성공화면 출력
                        printf("***** SUCCESS *****\n");
                        printf("*                 *\n");
                        printf("*   + %d  ->  + %d  *\n", level, level + 1);
                        printf("*                 *\n");
                        printf("***** SUCCESS *****\n");

                        // 학습에 성공 했을 시, 레벨을 하나 증가 시키고, 성공확률을 보정
                        // 이 때, 현재 성공확률의 10%에 현재 레벨로 가중치를 추가로 적용
                        level++;
                        probability -= 5.0f;


                        // 강화 성공 시 강화 비용 추가 및 증가
                        money -= enhancementCost;
                        enhancementCost += ENHANCEMENT_COST_INCREASE;
                    }
                    else {
                        // 실패화면 출력
                        printf("어익후.. 핸드폰을 봤네..교수님이 봐버렸다...\n");
                        printf("+ %d 지식을 잃었습니다.\n", level);

                        // 복습권 사용 여부 물어보기
                        int useReviewTicket;
                        printf("복습권을 사용하시겠습니까? (1: 예, 0: 아니오) ");
                        scanf_s("%d", &useReviewTicket);

                        if (useReviewTicket == 1 && reviewTickets > 0) {
                            printf("복습권을 사용하여 학생 레벨이 유지됩니다.\n");
                            reviewTickets--; // 복습권 사용
                        }
                        else {
                            // 학습에 실패 했을 시, 레벨 초기화 및 성공확률 초기화
                            level = 0;
                            probability = MAX_PROBABILITY;

                            // 강화 실패 시 강화 비용 초기화
                            enhancementCost = BASE_ENHANCEMENT_COST;
                        }
                    }
                }
            }

            break;

        case 2:
            // 포기를 할 경우 프로그램 종료
            printf("이지호 학생 키우기 게임을 포기하셨습니다.. 안녕히 가세요~ ~\n");
            return -1;

        case 3:
            // 상점에 입장하는 메시지 출력
            printf("\n상점으로 이동\n\n");

            // 상점에서 무엇을 할지 구현 가능
            printf("학습 재화를 사용하여 아이템을 구매할 수 있습니다.\n");
            printf("1. 학생 판매\n");
            printf("2. 복습권 구매\n");
            printf("3. 뒤로 가기\n");

            int shopChoice;
            scanf_s("%d", &shopChoice);

            switch (shopChoice)
            {
            case 1:
                if (level > 0) { // 학생 레벨이 0보다 클 때만 학생 판매 옵션을 출력
                    // 재화가 0 미만으로 내려가지 않도록 처리
                    if (money < 0) {
                        money = 0;
                    }
                    // 강화를 판매하는 코드
                    printf("강화한 레벨: + %d\n", level);
                    printf("판매 금액: %d\n", enhancementCost);
                    // 재화 추가
                    money += enhancementCost;
                    // 강화 비용 초기화
                    enhancementCost = BASE_ENHANCEMENT_COST;
                    // 강화 확률 초기화
                    probability = MAX_PROBABILITY;
                    // 강화 레벨 초기화
                    level = 0;
                }
                else {
                    printf("학생 레벨이 0이므로 학생 판매 옵션을 사용할 수 없습니다.\n");
                }
                break;
            case 2:
                // 복습권 구매
                if (money < REVIEW_TICKET_COST) {
                    printf("재화가 부족하여 복습권을 구매할 수 없습니다.\n");
                }
                else {
                    // 아이템을 구매하는 코드를 작성
                    printf("복습권을 구매하였습니다.\n");
                    // 재화 차감
                    money -= REVIEW_TICKET_COST;
                    // 복습권 개수 증가
                    reviewTickets++;
                }
                break;
            case 3:
                // 뒤로 가기
                break;
            default:
                printf("잘못된 입력입니다.\n");
                break;
            }
            break;
        }

        // 진행상황 확인이 용이 하도록 대기
        printf("\n계속 하시려면 스페이스바를 눌러주세요!\n");
        _getch();

        // 학생 레벨이 20 이상인 경우
        if (level >= 20) {
            printf("\n수고하셨습니다. 이지호 학생의 학습이 끝났습니다.\n");
            printf("\n수고하셨습니다. 이지호 학생의 학습이 끝났습니다.\n");
            printf("게임을 계속 진행하시려면 다시 시작하세요!\n");
            _getch(); // 사용자가 잠시 기다리도록 함
        }
    }

    return 0;
}