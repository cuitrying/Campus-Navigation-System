#include "mainwindow.h"

void MainWindow::findShortestPath::findPath(int startPos, int flag){  //迪杰斯特拉算法，求出起点到各点的最短距离

    if(flag == 1){
        qDebug()<<"\n最短时间\n";
        qDebug()<<"\nflag"<<flag;
    }

    //赋初始值
    for(int i =0; i<Map.vexnum; i++)    {distance[i]=INF;}
    for(int i =0; i<Map.vexnum; i++)    {used[i]=false;}
    for(int i =0; i<Map.vexnum; i++)    {prev[i]=-1;}

    distance[startPos]=0.0;//第一个点的距离

    while(true){
        int v =-1;
        for(int u=0; u<Map.vexnum;u++){
            if(!used[u]&&(v==-1||distance[u]<distance[v]))
                v=u;
        }

        if(v==-1)   break;  //全被记录过或者
        used[v] = true;

        for(int u=0; u<Map.vexnum; u++){
            if(distance[u]>distance[v]+Map.arc[v][u].dis * (1 + flag*Map.congestion[v][u])){  //如果u距离大于u-v的距离，更新并记录
                distance[u]=distance[v]+Map.arc[v][u].dis * (1 + flag*Map.congestion[v][u]);
                prev[u]=v;
            }
        }
    }
    //for(int i =0; i<Map.vexnum; i++)    {qDebug()<<i<<" "<<prev[i]<<"\n";}
}

MainWindow::findShortestPath::findShortestPath(){
    //创建图，把边设置为最长或不可达，设置结点数、边数
    Map.vexnum=114;
    for(int i=0; i<Map.vexnum; i++)
        Map.vex.push_back(i);
    Map.arcnum = 200;
    for(int i =0; i<Map.vexnum; i++){
        for(int j =0 ; j<Map.vexnum; j++){
            if(i==j)
                Map.arc[i][j].dis=0;
            else
                Map.arc[i][j].dis=INF;
        }
    }
}

QVector<int> MainWindow::findShortestPath::getPath(int endPos){
    //用一个vector装路径上各结点，数组中是倒着的，所以要reverse
    QVector<int> pathRes;

    for(; endPos!=-1; endPos = prev[endPos]){
        qDebug()<<"endpos+1:"<<(endPos+1)<<"...\n";
        //qDebug()<<(endPos)<<"...\n";
        pathRes.push_back(endPos);
    }
    std::reverse(pathRes.begin(), pathRes.end());

    if(pathRes.size()!=0){
        return pathRes;
    }
    else{
        pathRes.push_back(endPos);
        return pathRes;
    }

    return pathRes;
}

void MainWindow::findShortestPath::setCongestion(){     //使用最短时间时调用

    int i,j;//排除112，113这两个中途点
        //float CrowdingDegree[114][114]={1.0};//这个可以放全局变量
    for(i=0;i<114;i++){
            for(j=i+1;j<114;j++){
                Map.congestion[i][j] = 0.0;
                Map.congestion[j][i] = 0.0;
            }
        }

    for(i=0;i<112;i++){
        for(j=i+1;j<112;j++){
            if(Map.arc[i][j].dis!=9999){
               //srand(time(NULL));
               Map.congestion[i][j]=(QRandomGenerator::global()->bounded(5.0));//生成1~21的随机数，使用时乘以边长即为带有拥挤度的边长度
               Map.congestion[j][i]=Map.congestion[i][j];
              // qDebug()<<"i:"<<i<<" j:"<<j<<Map.congestion[i][j]<<"\n";
            }
        }
    }
    //return 1;
}

void MainWindow::findShortestPath::createGraph(){

    //setCongestion();
    //输入边的信息——给数组元素赋值——复制粘贴保存好的边
/*
数组使用的是序号减一
01 雁北园北区西北角     02 雁北园北区东北角     03 医务室      04 综合办公楼东北角     05 运动场
06 雁北园北区西南角     07 雁北园北区        08 洗衣店      09 教工食堂     10 二维码广场        11 综合办公楼    12 综合办公楼东南角
13 东配楼      14 雁北园南区    15 小麦铺      16 球场       17 雁北园南区西       18 学生食堂
19 西餐厅      20 学生活动中心&邮局    21 校西门      22 快递站      23 鸿雁路西     24 沙河商贸服务区
25 鸿雁路中西     26 鸿雁路中    27 图书馆      28 教学实验综合楼&报告厅      29 鸿雁路东
30 雁南园S2    31 雁南园S3
32 雁南园S3后侧
33 雁南园S4    34 雁南园S4后侧      35 雁南园S5北       36 雁南园S6        37 雁南园S5南
*/
    Map.arc[0][1].dis = Map.arc[1][0].dis = 145;
    Map.arc[0][4].dis = Map.arc[4][0].dis = 40;
    Map.arc[1][2].dis = Map.arc[2][1].dis = 80;
    Map.arc[1][7].dis = Map.arc[7][1].dis = 90;
    Map.arc[2][3].dis = Map.arc[3][2].dis = 80;
    Map.arc[2][9].dis = Map.arc[9][2].dis = 90;
    Map.arc[3][11].dis = Map.arc[11][3].dis = 90;
    Map.arc[4][5].dis = Map.arc[5][4].dis = 50;
    Map.arc[5][6].dis = Map.arc[6][5].dis = 45;
    Map.arc[5][16].dis = Map.arc[16][5].dis = 50;
    Map.arc[6][7].dis = Map.arc[7][6].dis = 100;
    Map.arc[7][8].dis = Map.arc[8][7].dis = 40;
    Map.arc[8][9].dis = Map.arc[9][8].dis = 40;
    Map.arc[9][10].dis = Map.arc[10][9].dis = 50;
    Map.arc[10][11].dis = Map.arc[11][10].dis = 30;
    Map.arc[11][12].dis = Map.arc[12][11].dis = 160;
    Map.arc[13][7].dis = Map.arc[7][13].dis = 30;
    Map.arc[14][9].dis = Map.arc[9][14].dis = 35;
    Map.arc[15][16].dis = Map.arc[16][15].dis = 10;
    Map.arc[16][22].dis = Map.arc[22][16].dis = 55;
    Map.arc[17][13].dis = Map.arc[13][17].dis = 35;
    Map.arc[17][18].dis = Map.arc[18][17].dis = 80;
    Map.arc[17][24].dis = Map.arc[24][17].dis = 40;
    Map.arc[18][14].dis = Map.arc[14][18].dis = 40;
    Map.arc[18][25].dis = Map.arc[25][18].dis = 30;
    Map.arc[18][19].dis = Map.arc[19][18].dis = 45;
    Map.arc[19][11].dis = Map.arc[11][19].dis = 100;
    Map.arc[20][21].dis = Map.arc[21][20].dis = 20;
    Map.arc[21][22].dis = Map.arc[22][21].dis = 300;
    Map.arc[9][104].dis = Map.arc[104][9].dis = 9999;
    Map.arc[22][23].dis = Map.arc[23][22].dis = 100;
    Map.arc[23][24].dis = Map.arc[24][23].dis = 45;
    Map.arc[44][45].dis = Map.arc[45][44].dis = 37;
    Map.arc[44][48].dis = Map.arc[48][44].dis = 58;
    Map.arc[45][46].dis = Map.arc[46][45].dis = 37;
    Map.arc[45][51].dis = Map.arc[51][45].dis = 40;
    Map.arc[46][47].dis = Map.arc[47][46].dis = 38;
    Map.arc[47][49].dis = Map.arc[49][47].dis = 20;
    Map.arc[48][50].dis = Map.arc[50][48].dis = 20;
    Map.arc[49][52].dis = Map.arc[52][49].dis = 20;
    Map.arc[50][51].dis = Map.arc[51][50].dis = 75;
    Map.arc[50][108].dis = Map.arc[108][50].dis = 40;
    Map.arc[51][52].dis = Map.arc[52][51].dis = 75;
    Map.arc[51][56].dis = Map.arc[56][51].dis = 40;
    Map.arc[52][53].dis = Map.arc[53][52].dis = 25;
    Map.arc[52][109].dis = Map.arc[109][52].dis = 40;
    Map.arc[53][54].dis = Map.arc[54][53].dis = 120;
    Map.arc[53][60].dis = Map.arc[60][53].dis = 60;
    Map.arc[54][58].dis = Map.arc[58][54].dis = 25;
    Map.arc[55][56].dis = Map.arc[56][55].dis = 37;
    Map.arc[55][108].dis = Map.arc[108][55].dis = 38;

    Map.arc[24][25].dis = Map.arc[25][24].dis = 80;
    Map.arc[25][26].dis = Map.arc[26][25].dis = 80;
    Map.arc[26][27].dis = Map.arc[27][26].dis = 70;
    Map.arc[27][28].dis = Map.arc[28][27].dis = 90;
    Map.arc[28][12].dis = Map.arc[12][28].dis = 105;
    Map.arc[29][24].dis = Map.arc[24][29].dis = 48;
    Map.arc[29][30].dis = Map.arc[30][29].dis = 40;
    Map.arc[30][31].dis = Map.arc[31][30].dis = 80;
    Map.arc[30][32].dis = Map.arc[32][30].dis = 32;
    Map.arc[31][33].dis = Map.arc[33][31].dis = 30;
    Map.arc[33][22].dis = Map.arc[22][33].dis = 130;
    Map.arc[32][34].dis = Map.arc[34][32].dis = 40;
    Map.arc[34][33].dis = Map.arc[33][34].dis = 100;
    Map.arc[34][35].dis = Map.arc[35][34].dis = 130;
    Map.arc[35][36].dis = Map.arc[36][35].dis = 25;
    Map.arc[34][36].dis = Map.arc[36][34].dis = 50;
    Map.arc[70][75].dis = Map.arc[75][70].dis = 45;
    Map.arc[71][72].dis = Map.arc[72][71].dis = 38;
    Map.arc[71][83].dis = Map.arc[83][71].dis = 65;
    Map.arc[72][73].dis = Map.arc[73][72].dis = 37;
    Map.arc[73][74].dis = Map.arc[74][73].dis = 37;
    Map.arc[74][75].dis = Map.arc[75][74].dis = 38;
    Map.arc[75][76].dis = Map.arc[76][75].dis = 65;
    Map.arc[75][82].dis = Map.arc[82][75].dis = 15;
    Map.arc[75][85].dis = Map.arc[85][75].dis = 65;
    Map.arc[76][77].dis = Map.arc[77][76].dis = 60;
    Map.arc[77][78].dis = Map.arc[78][77].dis = 95;
    Map.arc[77][87].dis = Map.arc[87][77].dis = 65;
    Map.arc[78][79].dis = Map.arc[79][78].dis = 40;
    Map.arc[78][89].dis = Map.arc[89][78].dis = 65;
    Map.arc[79][80].dis = Map.arc[80][79].dis = 25;
//    Map.arc[20][81].dis = Map.arc[81][20].dis = 1000;//从沙河西门到本部东门
    //修改，增加转折点
    Map.arc[20][112].dis = Map.arc[112][20].dis = 500;
    Map.arc[112][113].dis = Map.arc[113][112].dis = 1000;
    Map.arc[113][81].dis = Map.arc[81][113].dis = 200;
/*
 本部序号，使用时所有序号+36
 * 01 校北门   02 学十一公寓03 经管楼04 学六公寓
05 家属区06 科研大楼07 校东北门&青年教师公寓
08 留学生公寓09 学九公寓10 学十公寓11 学生活动中心西门   12 青年公寓13 综合食堂
14 学五公寓西北角15 外卖窗口西16 外卖窗口东17 学苑超市18 水房澡堂锅炉房
19 学五公寓20 喷泉北21 学八公寓22 教工餐厅 23 喷泉东24 小松林25 学苑书屋

26 学十三公寓27 学三公寓28 喷泉南29 学四公寓30 学四东31 球场32 学生食堂33 家属区&保卫处 34 图书馆
35 鸿雁楼36 学一公寓37 学一学二路口38 学二公寓39 时光广场路口40 行政办公楼41 篮球场西南角42 网球场排球场南43 体育馆44 游泳馆&学29公寓45 校东门
46 财务处&后勤楼  47 移动营业厅48 教四楼49 主干道中50 教一楼51 教一楼东南角52 科学会堂53 全民健身
54 校西门&主席像55 主楼&音乐喷泉 56 体育场
57 停车坪58 教三楼59 主干道南60 教二楼61 教二楼东北角62 科学会堂西南角63 科学会堂东南角
64 中门邮局65 教二楼东南角66 可信网络通信协同创新中心  67 时光咖啡店68 校医院69 中门  70 南区超市 71 南门
72 学五公寓西南角73 学八公寓东南角74 校车车库75 体育场西南角
*/

    Map.arc[37][38].dis = Map.arc[38][37].dis = 115;
    Map.arc[37][39].dis = Map.arc[39][37].dis = 60;
    Map.arc[38][45].dis = Map.arc[45][38].dis = 40;
    Map.arc[39][47].dis = Map.arc[47][39].dis = 20;
    Map.arc[40][41].dis = Map.arc[41][40].dis = 60;
    Map.arc[41][42].dis = Map.arc[42][41].dis = 30;
    Map.arc[41][54].dis = Map.arc[54][41].dis = 70;
    Map.arc[42][43].dis = Map.arc[43][42].dis = 160;
    Map.arc[43][69].dis = Map.arc[69][43].dis = 200;
    Map.arc[90][93].dis = Map.arc[93][90].dis = 45;
    Map.arc[91][95].dis = Map.arc[95][91].dis = 55;
    Map.arc[92][99].dis = Map.arc[99][92].dis = 30;
    Map.arc[93][94].dis = Map.arc[94][93].dis = 75;
    Map.arc[93][110].dis = Map.arc[110][93].dis = 65;
    Map.arc[94][95].dis = Map.arc[95][94].dis = 75;
    Map.arc[95][96].dis = Map.arc[96][95].dis = 60;
    Map.arc[95][100].dis = Map.arc[100][95].dis = 65;
    Map.arc[96][97].dis = Map.arc[97][96].dis = 50;
    Map.arc[97][98].dis = Map.arc[98][97].dis = 5;
    Map.arc[97][101].dis = Map.arc[101][97].dis = 65;
    Map.arc[98][99].dis = Map.arc[99][98].dis = 55;
    Map.arc[99][111].dis = Map.arc[111][99].dis = 65;
    Map.arc[25][26].dis = Map.arc[26][25].dis = 80;
    Map.arc[26][27].dis = Map.arc[27][26].dis = 70;
    Map.arc[27][28].dis = Map.arc[28][27].dis = 90;
    Map.arc[28][12].dis = Map.arc[12][28].dis = 105;
    Map.arc[29][24].dis = Map.arc[24][29].dis = 48;
    Map.arc[29][30].dis = Map.arc[30][29].dis = 40;
    Map.arc[30][31].dis = Map.arc[31][30].dis = 80;
    Map.arc[30][32].dis = Map.arc[32][30].dis = 32;
    Map.arc[31][33].dis = Map.arc[33][31].dis = 30;
    Map.arc[33][22].dis = Map.arc[22][33].dis = 130;
    Map.arc[32][34].dis = Map.arc[34][32].dis = 40;
    Map.arc[34][33].dis = Map.arc[33][34].dis = 100;
    Map.arc[34][35].dis = Map.arc[35][34].dis = 130;
    Map.arc[35][36].dis = Map.arc[36][35].dis = 25;
    Map.arc[34][36].dis = Map.arc[36][34].dis = 50;

    Map.arc[44][45].dis = Map.arc[45][44].dis = 37;
    Map.arc[44][48].dis = Map.arc[48][44].dis = 58;
    Map.arc[45][46].dis = Map.arc[46][45].dis = 37;
    Map.arc[45][51].dis = Map.arc[51][45].dis = 40;
    Map.arc[46][47].dis = Map.arc[47][46].dis = 38;
    Map.arc[47][49].dis = Map.arc[49][47].dis = 20;
    Map.arc[48][50].dis = Map.arc[50][48].dis = 20;
    Map.arc[49][52].dis = Map.arc[52][49].dis = 20;
    Map.arc[50][51].dis = Map.arc[51][50].dis = 75;
    Map.arc[50][108].dis = Map.arc[108][50].dis = 40;
    Map.arc[51][52].dis = Map.arc[52][51].dis = 75;
    Map.arc[51][56].dis = Map.arc[56][51].dis = 40;
    Map.arc[52][53].dis = Map.arc[53][52].dis = 25;
    Map.arc[52][109].dis = Map.arc[109][52].dis = 40;
    Map.arc[53][54].dis = Map.arc[54][53].dis = 120;
    Map.arc[53][60].dis = Map.arc[60][53].dis = 60;
    Map.arc[54][58].dis = Map.arc[58][54].dis = 25;
    Map.arc[55][56].dis = Map.arc[56][55].dis = 37;
    Map.arc[55][108].dis = Map.arc[108][55].dis = 38;
    Map.arc[56][57].dis = Map.arc[57][56].dis = 37;
    Map.arc[56][64].dis = Map.arc[64][56].dis = 35;
    Map.arc[57][109].dis = Map.arc[109][57].dis = 38;
    Map.arc[58][61].dis = Map.arc[61][58].dis = 35;
    Map.arc[59][60].dis = Map.arc[60][59].dis = 25;
    Map.arc[59][66].dis = Map.arc[66][59].dis = 10;
    Map.arc[59][109].dis = Map.arc[109][59].dis = 25;
    Map.arc[60][61].dis = Map.arc[61][60].dis = 120;
    Map.arc[61][67].dis = Map.arc[67][61].dis = 30;
    Map.arc[62][63].dis = Map.arc[63][62].dis = 38;
    Map.arc[62][71].dis = Map.arc[71][62].dis = 90;
    Map.arc[62][108].dis = Map.arc[108][62].dis = 35;
    Map.arc[63][64].dis = Map.arc[64][63].dis = 37;
    Map.arc[64][65].dis = Map.arc[65][64].dis = 37;
    Map.arc[64][73].dis = Map.arc[73][64].dis = 90;
    Map.arc[65][66].dis = Map.arc[66][65].dis = 38;
    Map.arc[66][70].dis = Map.arc[70][66].dis = 45;
    //Map.arc[66][75].dis = Map.arc[75][66].dis = 90;
    Map.arc[67][68].dis = Map.arc[68][67].dis = 30;
    Map.arc[67][77].dis = Map.arc[77][67].dis = 70;
    Map.arc[68][69].dis = Map.arc[69][68].dis = 105;
    Map.arc[69][79].dis = Map.arc[79][69].dis = 70;
    Map.arc[70][75].dis = Map.arc[75][70].dis = 45;
    Map.arc[71][72].dis = Map.arc[72][71].dis = 38;
    Map.arc[71][83].dis = Map.arc[83][71].dis = 65;
    Map.arc[72][73].dis = Map.arc[73][72].dis = 37;
    Map.arc[73][74].dis = Map.arc[74][73].dis = 37;
    Map.arc[74][75].dis = Map.arc[75][74].dis = 38;
    Map.arc[75][76].dis = Map.arc[76][75].dis = 65;
    Map.arc[75][82].dis = Map.arc[82][75].dis = 15;
    Map.arc[75][85].dis = Map.arc[85][75].dis = 65;
    Map.arc[76][77].dis = Map.arc[77][76].dis = 60;
    Map.arc[77][78].dis = Map.arc[78][77].dis = 95;
    Map.arc[77][87].dis = Map.arc[87][77].dis = 65;
    Map.arc[78][79].dis = Map.arc[79][78].dis = 40;
    Map.arc[78][89].dis = Map.arc[89][78].dis = 65;
    Map.arc[79][80].dis = Map.arc[80][79].dis = 25;
    Map.arc[80][81].dis = Map.arc[81][80].dis = 20;
    Map.arc[82][85].dis = Map.arc[85][82].dis = 50;
    Map.arc[83][84].dis = Map.arc[84][83].dis = 75;
    Map.arc[83][90].dis = Map.arc[90][83].dis = 65;
    Map.arc[84][85].dis = Map.arc[85][84].dis = 75;
    Map.arc[85][86].dis = Map.arc[86][85].dis = 65;
    Map.arc[85][91].dis = Map.arc[91][85].dis = 65;
    Map.arc[86][87].dis = Map.arc[87][86].dis = 60;
    Map.arc[87][88].dis = Map.arc[88][87].dis = 30;
    Map.arc[87][98].dis = Map.arc[98][87].dis = 110;
    Map.arc[88][89].dis = Map.arc[89][88].dis = 25;
    Map.arc[89][92].dis = Map.arc[92][89].dis = 80;
    Map.arc[90][93].dis = Map.arc[93][90].dis = 45;
    Map.arc[91][95].dis = Map.arc[95][91].dis = 55;
    Map.arc[92][99].dis = Map.arc[99][92].dis = 30;
    Map.arc[93][94].dis = Map.arc[94][93].dis = 75;
    Map.arc[93][110].dis = Map.arc[110][93].dis = 65;
    Map.arc[94][95].dis = Map.arc[95][94].dis = 75;
    Map.arc[95][96].dis = Map.arc[96][95].dis = 60;
    Map.arc[95][100].dis = Map.arc[100][95].dis = 65;
    Map.arc[96][97].dis = Map.arc[97][96].dis = 50;
    Map.arc[97][98].dis = Map.arc[98][97].dis = 5;
    Map.arc[97][101].dis = Map.arc[101][97].dis = 65;
    Map.arc[98][99].dis = Map.arc[99][98].dis = 55;
    Map.arc[99][111].dis = Map.arc[111][99].dis = 65;
    Map.arc[100][101].dis = Map.arc[101][100].dis = 120;
    Map.arc[100][105].dis = Map.arc[105][100].dis = 35;
    Map.arc[100][110].dis = Map.arc[110][100].dis = 150;
    Map.arc[101][102].dis = Map.arc[102][101].dis = 30;
    Map.arc[102][111].dis = Map.arc[111][102].dis = 30;
    Map.arc[103][104].dis = Map.arc[104][103].dis = 70;
    Map.arc[104][105].dis = Map.arc[105][104].dis = 35;
    Map.arc[105][106].dis = Map.arc[106][105].dis = 20;
    Map.arc[106][107].dis = Map.arc[107][106].dis = 164;



}
