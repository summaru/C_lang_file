package com.lib;

public class User {
	
	private boolean prepaid;
	private String name;
	private String passwd;
	private String id;
	private long remainTime;
	
	public User(){
		
	}
	
	public User(String id,String passwd,String name){
		this.name = name;
		this.passwd = passwd;
		this.id = id;
		this.remainTime = 0;
	}
	
	public String getId() {
		return id;
	}

	public boolean isPrepaid() {
		return prepaid;
	}

	public void setPrepaid(boolean prepaid) {
		this.prepaid = prepaid;
	}

	public void setId(String id) {
		this.id = id;
	}

	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getPasswd() {
		return passwd;
	}
	public void setPasswd(String passwd) {
		this.passwd = passwd;
	}

	public long getRemainTime() {
		return remainTime;
	}

	public void setRemainTime(long remainTime) {
		this.remainTime = remainTime;
	}
	
}
