package main

import (
	"golang.org/x/net/html"
	"io"
	"github.com/PuerkitoBio/goquery"
	"strings"
	"fmt"
)

func Parsing(source io.Reader) (io.Reader,error) {
	
	node,nodeErr := html.Parse(source)
	if nodeErr != nil {return nil,nodeErr}
	doc := goquery.NewDocumentFromNode(node)
	fmt.Println("html 문서 파싱중...")
	selectors := doc.Find("yt-formatted-string#content-text")
	
	return strings.NewReader(selectors.Text()),nil
}