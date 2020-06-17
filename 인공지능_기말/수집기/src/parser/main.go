package main

import (
	"bytes"
	"io"
	"io/ioutil"
	"log"
	"os"
)

func main() {

	if len(os.Args) < 3{
		log.Println("parser :첫번째 인자는 html문서," + 
			"두번째 인자는 저장할 데이터 경로를 입력하세요")
		os.Exit(2)	
	}

	htmlPath := os.Args[1]
	outputPath := os.Args[2]

	htmlSource,htmlErr :=ioutil.ReadFile(htmlPath)
	if htmlErr != nil {
		log.Println("parser: html를 불려오는데 실패했습니다.")
		log.Println("에러메세지 :"+htmlErr.Error()+"")
		os.Exit(2)
	}
	
	reader,parErr:=Parsing(bytes.NewBuffer(htmlSource))
	if parErr != nil {
		log.Println("parser: html파싱을 실패했습니다.")
		log.Println("에러메세지 :"+htmlErr.Error()+"")
		os.Exit(2)
	}

	output,outOpenErr := os.OpenFile(outputPath,
		os.O_CREATE | os.O_TRUNC | os.O_RDWR,os.FileMode(0644))
	defer output.Close()
	
	if outOpenErr != nil {
		log.Println("출력 파일 생성이 안됩니다.")
		log.Println("에러메세지 :"+outOpenErr.Error())
		os.Exit(2)
	}

	_,copyErr := io.Copy(output,reader)
	if copyErr != nil {
		log.Println("파일 쓰기가 실패했습니다.")
		log.Println("에러 메세지: "+copyErr.Error())
		os.Exit(2)
	}
	log.Println("파싱 done!")
}

