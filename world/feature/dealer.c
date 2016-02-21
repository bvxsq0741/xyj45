// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */

// dealer.c ����
// This is a inheritable object.
// Each dealer should support buy, sell, list, value 4 commands

#include <dbase.h>

string is_vendor_good(string arg)
{
	string *goods;
	object ob;
	int i;

	if (arrayp(goods = query("vendor_goods"))) 
		for (i = 0; i < sizeof(goods); i++) 
			if (goods[i]->id(arg))
				return goods[i];
	return "";
}

int do_value(string arg)
{
	object ob;
	int value;

	if (!arg || !(ob = present(arg, this_player())))
		return notify_fail("��Ҫ��ʲô�ļۣ�\n");
	
	if (ob->query("money_id"))
		return notify_fail("��û�ù�Ǯ����\n");

	value = ob->query("value");
	if (value < 1)
		write(ob->query("name") + "һ�Ĳ�ֵ��\n");
	else 
		write(ob->query("name") + "ֵ" + 
		MONEY_D->price_str(value * 70 / 100) + "��\n");
	return 1;
}

int do_sell(string arg)
{
	object ob;
	int value;
	
	if (!arg || !(ob = present(arg, this_player())))
		return notify_fail("��Ҫ��ʲô��\n");

	if (ob->query("money_id"))
		return notify_fail("��������Ǯ������\n");

	if (stringp(ob->query("no_drop")))
		return notify_fail("����������������\n");

	if (is_vendor_good(arg) != "") 
		return notify_fail("������ò��ã�\n");

	if (ob->query("food_supply"))
		return notify_fail("ʣ��ʣ���������Լ��ðɡ�\n");
	
        if (ob->query("shaolin"))
                return notify_fail("С��ֻ��һ���Դ����ɲ���������������\n");
	
	value = ob->query("value");
	if (value < 30)
		write(ob->query("name") + "һ�Ĳ�ֵ��\n");
	else {
		message_vision("$N������һ" + ob->query("unit") + 
		ob->query("name") + "��$n��\n", this_player(), this_object());
		MONEY_D->pay_player(this_player(), value * 70 / 100);
		if (value < 50)
			destruct(ob);
		else
			ob->move(this_object());
	}
	return 1;
}

int do_list()
{
	string *goods;
	object *inv;
	int i;

	inv = all_inventory(this_object());

	if (!sizeof(inv) && !arrayp(goods = query("vendor_goods")))
		return notify_fail("Ŀǰû�п������Ķ�����\n");
	
	printf("�������%s����������Ʒ��\n", query("name"));
	for (i = 0; i < sizeof(inv); i++) 
		if (!inv[i]->query("equipped") && !inv[i]->query("money_id"))
		printf("%30-s��%s\n", inv[i]->short(),
		MONEY_D->price_str(inv[i]->query("value") * 6 / 5));
	if (arrayp(goods = query("vendor_goods")))
		for (i = 0; i < sizeof(goods); i++)
			printf("%30-s��%s\n", goods[i]->short(),
			MONEY_D->price_str(goods[i]->query("value")));
	return 1;
}	

int do_buy(string arg)
{
	int value, val_factor;
	string ob_file;
	object ob;
//	mapping fam;

//      if ( (fam = this_player()->query("family")) && fam["family_name"] == "ؤ��" ) 
//		return notify_fail("���Ǹ���л�����ʲ�ᶫ����\n");
	
	if (!arg)
		return notify_fail("������ʲô�� 1\n");
	else if (!(ob = present(arg, this_object())))
		if ((ob_file = is_vendor_good(arg)) == "")
			return notify_fail("������ʲô�� 2\n");

	if (!ob) {
		ob = new(ob_file);
		val_factor = 10;
	}
	else {
		if (ob->query("equipped"))
			return notify_fail("������ʲô�� 3\n");
		val_factor = 12;
	}

        if (query_temp("busy"))
                return notify_fail("Ӵ����Ǹ�����������æ���ء��������Ժ�\n");

	
	switch (MONEY_D->player_pay(this_player(), ob->query("value") *  val_factor / 10)) {
	case 0:
		return notify_fail("��⵰��һ�ߴ���ȥ��\n");
	case 2:
		return notify_fail("������Ǯ�����ˣ���Ʊ��û���ҵÿ���\n");
	default:
        	set_temp("busy", 1);
		message_vision("$N��$n����������һ" + ob->query("unit") + 
		ob->query("name") + "��\n", this_player(), this_object());
		ob->move(this_player());
	}
        remove_call_out("enough_rest");
        call_out("enough_rest", 1);

	return 1;
}

void enough_rest()
{
        delete_temp("busy");
}

