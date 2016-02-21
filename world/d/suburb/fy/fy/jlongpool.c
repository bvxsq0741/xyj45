
inherit ROOM;
#include <room.h>

void create()
{
        set("short", "����ԡ��");
        set("long", @LONG
һ���ţ��������棬�װ׵�ˮ�����̰�Χ���㡣����ϡ����һ���޴��̴ľˮ��,
ˮ�ʱ��̣�ɢ����һ�����ص�ҩ�㣬ˮ���ϻ�Ư��һƬƬ���Ļ������������һ��
������������𣩽�ȥ�������۾��úõķ���һ�¡�
LONG
        );
        set("exits", ([
                "east" : __DIR__"jlonglang3",
        ]));
        set("objects", ([
                __DIR__"npc/troublemaker": 2,
        ]) );
        setup();
        create_door("east", "̴ľ��", "west", DOOR_CLOSED);

}

void init()
{
	add_action("do_jump", "jump");

}

int do_jump()
{
	object me;
	int wait;
	me = this_player();
	wait = random( 40 - (int)(me->query("con"))) * 2;
	if ( wait <= 20) wait = 21;
	message_vision("$N����һ������ԡ�أ�\n",me);
	tell_object(me,"��е�ȫ���ޱȵ���̩����\n");
	remove_call_out("curehimup");
	call_out("curehimup", wait, me);
return 1;
}

void curehimup(object me)
{
        int gin,kee,sen;
        gin=(int)me->query("max_gin");
        kee=(int)me->query("max_kee");
        sen=(int)me->query("max_sen");
if( me && environment(me) == this_object())
	{
	message_vision("$N�ľ�����ȫ�ָ��ˣ���\n", me);
	me->set("eff_gin",gin);
        me->set("eff_kee",kee);
        me->set("eff_sen",sen);
	me->set("gin", gin);
        me->set("kee", kee);
        me->set("sen", sen);
	}
return;
}
