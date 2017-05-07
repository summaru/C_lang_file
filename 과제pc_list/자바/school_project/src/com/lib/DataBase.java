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
		System.out.print("�̸��� �Է��ϼ���:");
		Scanner scan = new Scanner(System.in);
		String name = scan.nextLine();
		
		if(checkCmpName(name) == true){
			System.out.println("�̹� �ִ� �̸��Դϴ�,ó������ ���Է��� �մϴ�");
			continue;
			}
		
		System.out.print("���̵� �Է��ϼ���:");
		String id = scan.nextLine();
		
		if(checkCmpId(id) == true){
			System.out.println("�̹� �ִ� ���̵��Դϴ�,ó������ ���Է��� �մϴ�");
			continue;
			}
		
		System.out.print("��A��ȣ�� �Է��ϼ���:");
		String passwd = scan.nextLine();
		
		userList.add(new User(id,passwd,name));
		System.out.println("ȸ�������� �Ϸ�Ǿ����ϴ�");
		SystemUtil.threeSencondCls();
		return;
		}
	}
	
	public void signIn(){
		Scanner scan = new Scanner(System.in);
		Scanner numScan = new Scanner(System.in);
		while(true){
			
			System.out.print("���̵� �Է��ϼ���");
			String id = scan.nextLine();
			User user = searchByUser(id);
			if(user == null){
				System.out.println("�ش� ������ �����ϴ�");
				continue;
			}
			System.out.print("��й�ȣ�� �Է��ϼ���");
			String pd = scan.nextLine();
			if(!user.getPasswd().equals(pd)){
				System.out.println("��й�ȣ�� Ʋ�Ƚ��ϴ�");
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
				System.out.print("��� �¼����� �Ͻðڽ��ϱ�?:");
				number = numScan.nextInt();
				System.out.println("�ٽ� �Է��Ͻʽÿ�");
			}
			Pc pc = pcList.get(number-1);
			
			if(pc.getonOff() == Pc.ON){
				System.out.print("�̹� ������� �¼��Դϴ�");
				continue;
			}
			
			if(user.getRemainTime() != 0){
				System.out.println("���ҿ��� �ĺҷ� ����� ���ҽð��� ������ϴ�");
			}
			
			System.out.print("1. ����,2. �ĺ�:");
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
			System.out.println("�α��� �Ϸ�");
			SystemUtil.threeSencondCls();
			return;
		}
		
	}
	public void signOut(){
		Scanner scan = new Scanner(System.in);
		System.out.print("���̵��� �Է��ϼ���");
		String id = scan.nextLine();
		for(Pc pc : pcList){
		
			if(pc.getonOff())
				if(pc.getUser().getId().equals(id)){
					System.out.print("���̵� ã�ҽ��ϴ�");
					pc.logOut();
					SystemUtil.threeSencondCls();
					return;
				}
		}
		System.out.print("ã�� ���߽��ϴ�");
		SystemUtil.threeSencondCls();
	}
	public void payEtc(){
		System.out.print("ID �Է�:");
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
		
		System.out.print("�ش� ������ �����ϴ�");
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
			System.out.print("exit�� �Է��Ͻø� ���θ޴��� ���ư��ϴ�");
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
			System.out.print("exit�� �Է��Ͻø� ���θ޴��� ���ư��ϴ�");
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

