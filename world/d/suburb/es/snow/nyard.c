// Room: "/d/snow/nyard.c

inherit ROOM;

void create()
{
	set("short", "�鷿");
	set("long", @LONG
������һ���������൱Ǭ�����鷿����ľ������������������Ե�
ʮ�ֿ��������������һ����ܣ��������һ���ŵĹ��飬�����߳���
�ſ��Կ����쾮��
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "south" : "/d/suburb/es/snow/inneryard",
]));

	set("objects", ([
		__DIR__"npc/girl":1 ]) );

	setup();
	replace_program(ROOM);
}