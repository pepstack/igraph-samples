/**
 * main.c
 *   small sna graph analysis.
 * api doc:
 *   https://igraph.org/c/doc/
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <igraph.h>

#define MAXCNT  100

/**
 * 日志表：
 *   什么(人/用户)（Wm, m=01,02,...,18) 参加（购买）了什么 [活动/道具] (En, n=1,2,...,14)
 */
static char* evtlogs[][2] = {
     {"W01", "E1"}
    ,{"W01", "E2"}
    ,{"W01", "E3"}
    ,{"W01", "E4"}
    ,{"W01", "E5"}
    ,{"W01", "E7"}
    ,{"W01", "E8"}
    ,{"W01", "E9"}

    ,{"W02", "E1"}
    ,{"W02", "E2"}
    ,{"W02", "E3"}
    ,{"W02", "E5"}
    ,{"W02", "E6"}
    ,{"W02", "E7"}
    ,{"W02", "E8"}

    ,{"W03", "E2"}
    ,{"W03", "E3"}
    ,{"W03", "E4"}
    ,{"W03", "E5"}
    ,{"W03", "E6"}
    ,{"W03", "E7"}
    ,{"W03", "E8"}
    ,{"W03", "E9"}

    ,{"W04", "E1"}
    ,{"W04", "E3"}
    ,{"W04", "E4"}
    ,{"W04", "E5"}
    ,{"W04", "E6"}
    ,{"W04", "E7"}
    ,{"W04", "E8"}

    ,{"W05", "E3"}
    ,{"W05", "E4"}
    ,{"W05", "E5"}
    ,{"W05", "E7"}

    ,{"W06", "E3"}
    ,{"W06", "E5"}
    ,{"W06", "E6"}
    ,{"W06", "E7"}

    ,{"W07", "E5"}
    ,{"W07", "E6"}
    ,{"W07", "E7"}
    ,{"W07", "E8"}

    ,{"W08", "E6"}
    ,{"W08", "E8"}
    ,{"W08", "E9"}

    ,{"W09", "E5"}
    ,{"W09", "E7"}
    ,{"W09", "E8"}
    ,{"W09", "E9"}

    ,{"W10", "E7"}
    ,{"W10", "E8"}
    ,{"W10", "E9"}
    ,{"W10", "E12"}

    ,{"W11", "E8"}
    ,{"W11", "E9"}
    ,{"W11", "E10"}
    ,{"W11", "E12"}

    ,{"W12", "E8"}
    ,{"W12", "E9"}
    ,{"W12", "E10"}
    ,{"W12", "E12"}
    ,{"W12", "E13"}
    ,{"W12", "E14"}

    ,{"W13", "E7"}
    ,{"W13", "E8"}
    ,{"W13", "E9"}
    ,{"W13", "E10"}
    ,{"W13", "E12"}
    ,{"W13", "E13"}
    ,{"W13", "E14"}

    ,{"W14", "E6"}
    ,{"W14", "E7"}
    ,{"W14", "E9"}
    ,{"W14", "E10"}
    ,{"W14", "E11"}
    ,{"W14", "E12"}

    ,{"W15", "E7"}
    ,{"W15", "E8"}
    ,{"W15", "E10"}
    ,{"W15", "E11"}
    ,{"W15", "E12"}
    ,{"W15", "E13"}
    ,{"W15", "E14"}

    ,{"W16", "E8"}
    ,{"W16", "E9"}

    ,{"W17", "E9"}
    ,{"W17", "E11"}

    ,{"W18", "E9"}
    ,{"W18", "E11"}
};


void build_woman_graph();


int main(int argc, char *argv[])
{
    int i;

    // 计算事件数
    int rows = (sizeof(evtlogs)/sizeof(evtlogs[0]));

    // 显示原始输入数据
    printf("input evtlogs = {(Woman) --> [Event]}:\n\n");

    for (i = 0; i < rows; i++) {
        printf("(%s) --> [%s]\n", evtlogs[i][0], evtlogs[i][1]);
    }

    build_woman_graph();

    return 0;
}


void build_woman_graph()
{
    // 用数组模拟 map
    int num_womans = 0;
    int woman_ids[MAXCNT];

    // 用数组模拟 map
    int num_events = 0;
    int event_ids[MAXCNT];

    // TODO:

}