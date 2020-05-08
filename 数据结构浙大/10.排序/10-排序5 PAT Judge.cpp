#include<iostream>
#include<algorithm>
using namespace std;
struct student {
	int id=-1;
	int prefectsolve=0;
	int score=0;
}stu[10000];
bool cmp(student a, student b)
{
	if (a.score == b.score)
	{
		if (a.prefectsolve == b.prefectsolve)
			return a.id < b.id;
		else
			return a.prefectsolve > b.prefectsolve;
	}
	else
		return a.score > b.score;
}	
int studentscore[10000][5] = { 0 };
bool input[10000][5] = { false };
void Print(int id,int problemnum)
{
	for (int i = 0; i < problemnum - 1; i++)
	{
		if (input[id-1][i]==true)
			printf("%d ", studentscore[id - 1][i]);
		else
			printf("- ");
	}
	if (input[id - 1][problemnum - 1] ==true)
		printf("%d\n", studentscore[id - 1][problemnum - 1]);
	else
		printf("-\n");
}
int main()
{
	int usernum, problemnum, submissionnum;
	bool Ranklist[10000] = { false };
	scanf("%d%d%d", &usernum, &problemnum, &submissionnum);
	int* point = (int*)malloc(problemnum * sizeof(int));
	for (int i = 0; i < problemnum; i++)
		scanf("%d", &point[i]);
	int user_id,problem_id,partial_score_obtained;
	for(int i=0;i<submissionnum;i++)
	{
		scanf("%d%d%d", &user_id, &problem_id, &partial_score_obtained);
		if (partial_score_obtained == -1)
			partial_score_obtained = 0;
		else
			Ranklist[user_id-1] = true;
		if (studentscore[user_id - 1][problem_id - 1] < partial_score_obtained)
			studentscore[user_id - 1][problem_id - 1] = partial_score_obtained;
		input[user_id - 1][problem_id - 1] = true;
	}
	for (int i = 0; i < usernum; i++)
	{
		stu[i].id = i + 1;
		int ps = 0;
		int scoresum=0;
		for (int j = 0; j < problemnum; j++)
		{
			if (point[j] == studentscore[i][j])
				ps++;
			scoresum += studentscore[i][j];
		}
		stu[i].prefectsolve = ps;
		stu[i].score = scoresum;
	}
	sort(stu, stu + usernum, cmp);
	int rank = 1;
	printf("1 %05d %d ", stu[0].id,stu[0].score);
	Print(stu[0].id,problemnum);
	for (int i = 1; i < usernum; i++)
	{
		if (Ranklist[stu[i].id-1])//只要提交过能编译的程序就排行
		{
			if (stu[i].score == stu[i - 1].score)
				;//rank不变
			else
				rank = i + 1;
			printf("%d %05d %d ", rank, stu[i].id, stu[i].score);
			Print(stu[i].id, problemnum);
		}
	}
}
/*
1 00002 63 20 25 - 18
2 00005 42 20 0 22 -
2 00007 42 - 25 - 17
*/