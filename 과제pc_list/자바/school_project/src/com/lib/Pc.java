package com.lib;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

import com.lib.etc.Etc;
import com.lib.etc.Ramen;
import com.lib.etc.Snack;

public class Pc {
	public static final boolean ON = true;
	public static final boolean OFF = false;
	
	private boolean onOff;
	private User user;
	private int number;
	private long time;
	private int money;
	private List<Etc> etcList;
	
	private void ouputPripaidTime(long time){
		long h = time/3600;
		long m = (time%3600)/60;
		System.out.println(h+" �� "+m+" �� ");
		
	}
	
	private void payProcess(){
		long pcTime = getCountingTime();
		long hour = SystemUtil.operatorHour(pcTime);
		
		if(user.isPrepaid()){
			long userTime = user.getRemainTime();
			long usedSecond = getCountingTime();
			long remain = userTime-usedSecond;
			System.out.print("����� �ð�     : ");
			ouputPripaidTime(usedSecond);
			System.out.print("���� �ð�        : ");
			ouputPripaidTime(remain);
			for(Etc etc : etcList){
				System.out.println("|"+etc.getClassName()+"�� ���� |: "
						+etc.getMoney()+"|");
				money += etc.getMoney();
			}
			user.setRemainTime(remain);
		}
		else{	
			System.out.println("�÷��� �ð� : "+hour+"h(��)");
			money = (int)hour*1000;
			for(Etc etc : etcList){
				System.out.println("|"+etc.getClassName()+"�� ���� |: "
						+etc.getMoney()+"|");
				money += etc.getMoney();
			}
		}
		
	}
	

	public Pc(int num){
		this.number = num;
		onOff = OFF;
		money = 0;
		etcList = new ArrayList<Etc>();
	}
	public void logIn(User user,boolean paid){
		
		
		if(paid == false){
			this.user = user;
			onOff = ON;
			this.user.setPrepaid(false);
			this.time = SystemUtil.getCurrentSecond();
			return;
		}
		if(paid == true){
			System.out.print("��ð� �����Ͻðڽ��ϱ�?(�ð��� 1000��):");
			Scanner scan = new Scanner(System.in);
			long t = scan.nextLong();
			long setTime = (3600*t);
			user.setPrepaid(true);
			user.setRemainTime(setTime);
			onOff = ON;
			this.user = user;
			System.out.print(t+"�ð� �����Ͽ����ϴ�");
			time = SystemUtil.getCurrentSecond();
		}
	}
	
	public boolean getonOff(){
		return onOff;
	}
	
	public void init(){
		onOff = OFF;
		etcList.clear();
		time = 0;
		money = 0;
		user = null;
	}
	public void logOut(){
		payProcess();
		System.out.println("�� �ݾ��� "+money+" �Դϴ�");
		System.out.println("�̿��� �־ �����մϴ�");
		SystemUtil.threeSencondCls();
		init();
	}
	
	public void payEtc(){
		
		System.out.print("������ ��ðڽ��ϱ�?(1. ���,2. ����3. ����):");
		Scanner scan = new Scanner(System.in);
		int cho = scan.nextInt();
		Etc etc = null;
		switch(cho){
		case 1:
			etc = new Ramen();
			etcList.add(etc);
			break;
		case 2:
			etc = new Snack();
			etcList.add(etc);
			break;
		default:
			System.out.print("error , ����ȭ������ ���ư��ϴ�");
			SystemUtil.threeSencondCls();
			return;
		}
		System.out.print("���ſϷ�");
		SystemUtil.threeSencondCls();
	}
	public User getUser(){
		return user;
	}
	
	public long getCountingTime(){
		return (SystemUtil.getCurrentSecond() - time);
	}
	
}
