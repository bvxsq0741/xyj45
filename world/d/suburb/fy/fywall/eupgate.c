inherit ROOM;
void create()
{
        set("short", "������¥");
        set("long", @LONG
��¥�ʷ��Σ��������Ǵ�����Ϣ����Ⱥ�������£���������Ⱥ��΢���еĲʴ���
�����Ƿ��Ƴǵ����ģ�����������Ҳ������ϡ�Ŀ������ƹ㳡���ĵ�������������
�ķ������಻�ϣ������С·��ϸС�����ߣ����������ڻ�ɫ�ķ���֮�䡣
LONG
        );
        set("exits", ([ /* sizeof() == 4 */
  "down" : "/d/suburb/fy/fy/egate",
  "north" : __DIR__"ewall1",
  "south" : __DIR__"ewall10",
]));
        set("outdoors", "fengyun");
        setup();
        replace_program(ROOM);
}