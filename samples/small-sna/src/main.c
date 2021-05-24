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

#define NUM_WOMANS  18
#define NUM_EVENTS  14

#define NUM_MAXCNT  (NUM_WOMANS * NUM_EVENTS)


/**
 * 日志表：
 *   什么(人/用户)（Wm, m=01,02,...,18) 参加（购买）了什么 [活动/道具] (En, n=1,2,...,14)
 */
static char* evtlogs[][2] = {
    /* 人  -> 活动 */
     {"W01", "E01"}
    ,{"W01", "E02"}
    ,{"W01", "E03"}
    ,{"W01", "E04"}
    ,{"W01", "E05"}
    ,{"W01", "E06"}
    ,{"W01", "E08"}
    ,{"W01", "E09"}

    ,{"W02", "E01"}
    ,{"W02", "E02"}
    ,{"W02", "E03"}
    ,{"W02", "E05"}
    ,{"W02", "E06"}
    ,{"W02", "E07"}
    ,{"W02", "E08"}

    ,{"W03", "E02"}
    ,{"W03", "E03"}
    ,{"W03", "E04"}
    ,{"W03", "E05"}
    ,{"W03", "E06"}
    ,{"W03", "E07"}
    ,{"W03", "E08"}
    ,{"W03", "E09"}

    ,{"W04", "E01"}
    ,{"W04", "E03"}
    ,{"W04", "E04"}
    ,{"W04", "E05"}
    ,{"W04", "E06"}
    ,{"W04", "E07"}
    ,{"W04", "E08"}

    ,{"W05", "E03"}
    ,{"W05", "E04"}
    ,{"W05", "E05"}
    ,{"W05", "E07"}

    ,{"W06", "E03"}
    ,{"W06", "E05"}
    ,{"W06", "E06"}
    ,{"W06", "E08"}

    ,{"W07", "E05"}
    ,{"W07", "E06"}
    ,{"W07", "E07"}
    ,{"W07", "E08"}

    ,{"W08", "E06"}
    ,{"W08", "E08"}
    ,{"W08", "E09"}

    ,{"W09", "E05"}
    ,{"W09", "E07"}
    ,{"W09", "E08"}
    ,{"W09", "E09"}

    ,{"W10", "E07"}
    ,{"W10", "E08"}
    ,{"W10", "E09"}
    ,{"W10", "E12"}

    ,{"W11", "E08"}
    ,{"W11", "E09"}
    ,{"W11", "E10"}
    ,{"W11", "E12"}

    ,{"W12", "E08"}
    ,{"W12", "E09"}
    ,{"W12", "E10"}
    ,{"W12", "E12"}
    ,{"W12", "E13"}
    ,{"W12", "E14"}

    ,{"W13", "E07"}
    ,{"W13", "E08"}
    ,{"W13", "E09"}
    ,{"W13", "E10"}
    ,{"W13", "E12"}
    ,{"W13", "E13"}
    ,{"W13", "E14"}

    ,{"W14", "E06"}
    ,{"W14", "E07"}
    ,{"W14", "E09"}
    ,{"W14", "E10"}
    ,{"W14", "E11"}
    ,{"W14", "E12"}

    ,{"W15", "E07"}
    ,{"W15", "E08"}
    ,{"W15", "E10"}
    ,{"W15", "E11"}
    ,{"W15", "E12"}
    ,{"W15", "E13"}
    ,{"W15", "E14"}

    ,{"W16", "E08"}
    ,{"W16", "E09"}

    ,{"W17", "E09"}
    ,{"W17", "E11"}

    ,{"W18", "E09"}
    ,{"W18", "E11"}
};


void build_womans_graph(int rows);

void build_events_graph(int rows);


int main(int argc, char *argv[])
{
    int i;

    // 计算事件数
    int rows = (sizeof(evtlogs)/sizeof(evtlogs[0]));

    // 显示原始输入数据
    printf("input evtlogs = {(Woman) --> [Event]}:\n\n");

    for (i = 0; i < rows; i++) {
        char *w = evtlogs[i][0];
        char *e = evtlogs[i][1];

        if (w[0] != 'W') {
            printf("error app woman.\n");
            exit(-1);
        }

        if (e[0] != 'E') {
            printf("error app event.\n");
            exit(-1);
        }

        printf("(%s) --> [%s]\n", w, e);
    }

    build_womans_graph(rows);

    build_events_graph(rows);

    return 0;
}


void build_womans_graph(int rows)
{
    int i, j, k;

    // 对共现度求和 (非常适合用 flink 流式计算):
    //   2 个人 Wi, Wj 之间有连接仅当这 2 个人同时都参加了同一个活动 Ek

    igraph_t graph;
    igraph_empty(&graph, NUM_WOMANS, IGRAPH_UNDIRECTED);

    // 每一行 evt_wids[k] (k=0,1,2,... k < NUM_EVENTS) 是一个 int 数组, 代表参加了该事件的人列表
    int evt_wids[NUM_EVENTS][NUM_WOMANS];

    memset(evt_wids, 0, sizeof(int) * NUM_EVENTS  * NUM_WOMANS);

    for (k = 0; k < NUM_EVENTS; k++) {
        for (i = 0; i < rows; i++) {
            char *w = evtlogs[i][0];
            char *e = evtlogs[i][1];

            int wid = atoi(&w[1]);
            int eid = atoi(&e[1]);

            if (eid == k + 1) {
                evt_wids[k][wid - 1] = 1;
            }
        }
    }

    printf("\nwomans table:\n");
    printf("---------------\n");
    // 打印表头
    for (i = 0; i < NUM_WOMANS; i++) {
        if (i == 0) {
            printf("      W%02d", i + 1);
        } else {
            printf(", W%02d", i + 1);
        }
    }

    // 打印表
    for (k = 0; k < NUM_EVENTS; k++) {
        printf("\nE%02d=[ ", k + 1);
        for (i = 0; i < NUM_WOMANS; i++) {
            if (i == 0) {
                printf("%3d", evt_wids[k][i]);
            } else {
                printf(", %3d", evt_wids[k][i]);
            }
        }
        printf(" ]");
    }

    // 创建 woman 节点图
    for (k = 0; k < NUM_EVENTS; k++) {
        for (i = 0; i < NUM_WOMANS - 1; i++) {
            if (evt_wids[k][i] > 0) {
                for (j = i + 1; j < NUM_WOMANS; j++) {
                    if (evt_wids[k][j] > 0) {
                        printf("\nE%02d (W%02d --- W%02d)", k+1, i+1, j+1);
                    }
                }
            }
        }
    }

    printf("\n{ womans graph } vertices: %d, edges: %d\n", (int)igraph_vcount(&graph), (int)igraph_ecount(&graph));
    igraph_destroy(&graph);
}


void build_events_graph(int rows)
{
    int i, j, k;

    // 对共现度求和 (非常适合用 flink 流式计算):
    // 2 个活动 Em, En 之间有连接仅当同一个人 Wk 参加了2 个活动 Em, En
    igraph_t graph;
    igraph_empty(&graph, NUM_EVENTS, IGRAPH_UNDIRECTED);

    // 每一行 wmn_eids[k] (k=0,1,2,... k < NUM_WOMANS) 是一个 int 数组, 代表人参加的事件列表
    int wmn_eids[NUM_WOMANS][NUM_EVENTS];
    memset(wmn_eids, 0, sizeof(int) * NUM_EVENTS  * NUM_WOMANS);

    for (k = 0; k < NUM_WOMANS; k++) {
        for (i = 0; i < rows; i++) {
            char *w = evtlogs[i][0];
            char *e = evtlogs[i][1];

            int wid = atoi(&w[1]);
            int eid = atoi(&e[1]);

            if (wid == k + 1) {
                wmn_eids[k][eid - 1] = 1;
            }
        }
    }

    printf("\nevents table:\n");
    printf("---------------\n");

    // 打印表头
    for (i = 0; i < NUM_EVENTS; i++) {
        if (i == 0) {
            printf("      E%02d", i + 1);
        } else {
            printf(", E%02d", i + 1);
        }
    }

    // 打印表
    for (k = 0; k < NUM_WOMANS; k++) {
        printf("\nW%02d=[ ", k + 1);
        for (i = 0; i < NUM_EVENTS; i++) {
            if (i == 0) {
                printf("%3d", wmn_eids[k][i]);
            } else {
                printf(", %3d", wmn_eids[k][i]);
            }
        }
        printf(" ]");
    }

    // 创建 event 节点图
    for (k = 0; k < NUM_WOMANS; k++) {
        for (i = 0; i < NUM_EVENTS - 1; i++) {
            if (wmn_eids[k][i] > 0) {
                for (j = i + 1; j < NUM_EVENTS; j++) {
                    if (wmn_eids[k][j] > 0) {
                        printf("\nW%02d (E%02d --- E%02d)", k+1, i+1, j+1);
                    }
                }
            }
        }
    }

    printf("\n{ events graph } vertices: %d, edges: %d\n", (int)igraph_vcount(&graph), (int)igraph_ecount(&graph));
    igraph_destroy(&graph);
}