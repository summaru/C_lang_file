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
		System.out.println(h+" 시 "+m+" 분 ");
		
	}
	
	private void payProcess(){
		long pcTime = getCountingTime();
		long hour = SystemUtil.operatorHour(pcTime);
		
		if(user.isPrepaid()){
			long userTime = user.getRemainTime();
			long usedSecond = getCountingTime();
			long remain = userTime-usedSecond;
			System.out.print("사용한 시간     : ");
			ouputPripaidTime(usedSecond);
			System.out.print("남은 시간        : ");
			ouputPripaidTime(remain);
			for(Etc etc : etcList){
				System.out.println("|"+etc.getClassName()+"의 가격 |: "
						+etc.getMoney()+"|");
				money += etc.getMoney();
			}
			user.setRemainTime(remain);
		}
		else{	
			System.out.println("플레이 시간 : "+hour+"h(시)");
			money = (int)hour*1000;
			for(Etc etc : etcList){
				System.out.println("|"+etc.getClassName()+"의 가격 |: "
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
			System.out.print("몇시간 충전하시겠습니까?(시간당 1000원):");
			Scanner scan = new Scanner(System.in);
			long t = scan.nextLong();
			long setTime = (3600*t);
			user.setPrepaid(true);
			user.setRemainTime(setTime);
			onOff = ON;
			this.user = user;
			System.out.print(t+"시간 결제하였습니다");
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
		System.out.println("총 금액은 "+money+" 입니다");
		System.out.println("이용해 주어서 감사합니다");
		SystemUtil.threeSencondCls();
		init();
	}
	
	public void payEtc(){
		
		System.out.print("무엇을 사시겠습니까?(1. 라면,2. 스낵3. 종료):");
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
			System.out.print("error , 메인화면으로 돌아갑니다");
			SystemUtil.threeSencondCls();
			return;
		}
		System.out.print("구매완료");
		SystemUtil.threeSencondCls();
	}
	public User getUser(){
		return user;
	}
	
	public long getCountingTime(){
		return (SystemUtil.getCurrentSecond() - time);
	}
	
}
