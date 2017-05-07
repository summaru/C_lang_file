package com.lib;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class DataBase{

	public static final int MAXSIZE = 40;
	
	private List<Pc> pcList;
	private List<User> userList;
	private long start;
	
	public DataBase(){
		pcList = new ArrayList<Pc>();
		userList = new LinkedList<User>();
		start = SystemUtil.startTime;
		for(int i=0;i<MAXSIZE;i++){
			pcList.add(new Pc(i+1));
		}
	}
	
	public void signUp(){
		while(true){
		System.out.print("이름을 입력하세요:");
		Scanner scan = new Scanner(System.in);
		String name = scan.nextLine();
		
		if(checkCmpName(name) == true){
			System.out.println("이미 있는 이름입니다,처음부터 재입력을 합니다");
			continue;
			}
		
		System.out.print("아이디를 입력하세요:");
		String id = scan.nextLine();
		
		if(checkCmpId(id) == true){
			System.out.println("이미 있는 아이디입니다,처음부터 재입력을 합니다");
			continue;
			}
		
		System.out.print("비밃번호를 입력하세요:");
		String passwd = scan.nextLine();
		
		userList.add(new User(id,passwd,name));
		System.out.println("회원가입이 완료되었습니다");
		SystemUtil.threeSencondCls();
		return;
		}
	}
	
	public void signIn(){
		Scanner scan = new Scanner(System.in);
		Scanner numScan = new Scanner(System.in);
		while(true){
			
			System.out.print("아이디를 입력하세요");
			String id = scan.nextLine();
			User user = searchByUser(id);
			if(user == null){
				System.out.println("해당 유저는 없습니다");
				continue;
			}
			System.out.print("비밀번호를 입력하세요");
			String pd = scan.nextLine();
			if(!user.getPasswd().equals(pd)){
				System.out.println("비밀번호가 틀렸습니다");
				continue;
			}
			int number = 0;
			if(number < 1 || number > 40){
				int i = 1;
				for(Pc pc : pcList){
					if(pc.getonOff() == Pc.ON){
						String check = "ON";
						System.out.printf("|%2d : %4s|", i,check);
					}
					else if(pc.getonOff() == Pc.OFF){
						String check = "OFF";
						System.out.printf("|%2d : %4s|",  i,check);
					}
					
					if(i%10 == 0){
						System.out.println(" ");
					}
					i += 1;
				}
				System.out.print("몇번 좌석으로 하시겠습니까?:");
				number = numScan.nextInt();
				System.out.println("다시 입력하십시오");
			}
			Pc pc = pcList.get(number-1);
			
			if(pc.getonOff() == Pc.ON){
				System.out.print("이미 사용중인 좌석입니다");
				continue;
			}
			
			if(user.getRemainTime() != 0){
				System.out.println("선불에서 후불로 변경시 선불시간이 사라집니다");
			}
			
			System.out.print("1. 선불,2. 후불:");
			int cho = numScan.nextInt();
			boolean prePaid = false;
			if(cho > 2 && cho < 1){
				System.out.println("error");
				continue;
			}
			else if(cho == 1){
				prePaid = true;
			}
			else if(user.getRemainTime() != 0 && cho == 0){
				user.setRemainTime(0);
			}
			pc.logIn(user,prePaid);
			System.out.println("로그인 완료");
			SystemUtil.threeSencondCls();
			return;
		}
		
	}
	public void signOut(){
		Scanner scan = new Scanner(System.in);
		System.out.print("아이디을 입력하세요");
		String id = scan.nextLine();
		for(Pc pc : pcList){
		
			if(pc.getonOff())
				if(pc.getUser().getId().equals(id)){
					System.out.print("아이디를 찾았습니다");
					pc.logOut();
					SystemUtil.threeSencondCls();
					return;
				}
		}
		System.out.print("찾지 못했습니다");
		SystemUtil.threeSencondCls();
	}
	public void payEtc(){
		System.out.print("ID 입력:");
		Scanner scan = new Scanner(System.in);
		String id = scan.nextLine();
		for(Pc pc : pcList){
			if(pc.getonOff())
				if(pc.getUser().getId().equals(id)){
					pc.payEtc();
					SystemUtil.threeSencondCls();
					return;
				}
			
		}
		
		System.out.print("해당 유저가 없습니다");
		SystemUtil.threeSencondCls();
	}
	public void viewUserList(){
		System.out.printf("|%10s|%10s|%10s|\n","NAME","ID","PASSWD");
		for(User user : userList){
			System.out.printf("|%10s|%10s|%10s|\n", user.getName(),
					user.getId(),user.getPasswd());
		}
		String input="\0";
		Scanner scan = new Scanner(System.in);
		while(!input.equals("exit")){
			System.out.print("exit를 입력하시면 메인메뉴로 돌아갑니다");
			input = scan.nextLine();
		}
		SystemUtil.threeSencondCls();
	}
	public void viewPcList(){
		int i = 1;
		for(Pc pc : pcList){
			if(pc.getonOff() == Pc.ON){
				String check = "ON";
				System.out.printf("|%2d : %4s|", i,check);
			}
			else if(pc.getonOff() == Pc.OFF){
				String check = "OFF";
				System.out.printf("|%2d : %4s|",  i,check);
			}
			
			if(i%10 == 0){
				System.out.println(" ");
			}
			i += 1;
		}
		String input="\0";
		Scanner scan = new Scanner(System.in);
		while(!input.equals("exit")){
			System.out.print("exit를 입력하시면 메인메뉴로 돌아갑니다");
			input = scan.nextLine();
		}
		SystemUtil.threeSencondCls();
		scan = null;
	}
	
	
	private boolean checkCmpId(String id){
		for(User user: userList){
			if(user.getId().equals(id)){
				return true;
			}
		}
		return false;
	}
	private boolean checkCmpName(String name){
		for(User user : userList){
			if(user.getName().equals(name)){
				return true;
			}
		}
		return false;
	}
	
	private User searchByUser(String id){
		for(User user : userList){
			if(user.getId().equals(id)){
				return user;
			}
		}
		
		return null;
	}
	
}

