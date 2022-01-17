/*
一键杀死Adobe所有进程

只适用于Mac

1. 你可以把编译好的Unix可执行文件放入/usr/bin文件夹,换一个在该文件夹下,与任何文件名都不相冲突的名字,这样可以生成一个可以在终端运行的命令
2. 当然你也可以写一个com.killadobepro.plist开机自启任务文件,把它放入~/Library/LaunchAgents中
3. 直接点击运行编译好的Unix可执行文件
*/
#include <sys/types.h>
#include <libproc.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
pid_t pids[2048];

int sig=9;//杀死信号
//获取进程名的pid并杀死它
void kill_pro(const char *name)
{
    
    int bytes = proc_listpids(PROC_ALL_PIDS, 0, pids, sizeof(pids));//pid列表字节数
    int n_proc = bytes / sizeof(pids[0]);//进程数
    int n = 0;
    for (int i = 0; i < n_proc; i++) {
        struct proc_bsdinfo proc;//构造进程信息结构体
        int st = proc_pidinfo(pids[i], PROC_PIDTBSDINFO, 0,
                             &proc, PROC_PIDTBSDINFO_SIZE);
        if (st == PROC_PIDTBSDINFO_SIZE) {
            if (strcmp(name, proc.pbi_name) == 0) {
                /* Process PID */
                printf("%d [%s] [%s]", pids[i], proc.pbi_comm, proc.pbi_name);   
                int t = kill(pids[i], sig);//杀死进程返回状态,0:成功,-1:失败
                if(t==0){
                    printf(" : kill successful!\n");
                }else{
                    printf(" : kill failed\n");
                }     
            }
        }       
    }
    
}


int main()
{
    //adobe所有进程名
	char a[13][50] = {"Adobe_CCXProces", "AdobeIPCBroker", "Adobe Desktop Service", "Adobe CEF Helpe", "AdobeCRDaemon", "com.adobe.acc.installer.v2", "Creative Cloud", "Creative Cloud Helper", "CCXProcess", "Adobe_CCXProcess.node", "Adobe Installer", "CCLibrary", "Core Sync"};
    int n = sizeof(a)/sizeof(a[0]);//进程数

    printf("Adobe processes number = %d\n", n);
    printf("PID Name\n");
    for(int i=0; i<n;i++){
        kill_pro(a[i]);

    }

    return 0;
}
