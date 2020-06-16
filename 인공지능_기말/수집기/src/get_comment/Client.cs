using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using OpenQA.Selenium;
using OpenQA.Selenium.Firefox;
using System.Threading;
using OpenQA.Selenium.Support.UI;

namespace get_comment
{
    
    class Client
    {
        private int downCount=0;
        private IWebDriver driver;

        private string url;
        private IWebElement sectionY;

        int left = 0;
        int top = 0;
        public IWebDriver Dirver 
        {
            get
            {
                return driver;
            }
        }
       
        public Client(string url,int commentCount)
        {
            downCount = commentCount;
            FirefoxOptions options = new FirefoxOptions();
            options.AddArgument("--headless");
            driver = new FirefoxDriver(options);
            this.url = url;
            

            left = Console.CursorLeft;
            top = Console.CursorTop;
        }

        public string StartGetHTML(double timeout)
        {
            try 
            {
                driver.Navigate().GoToUrl(url);
            }
            catch(Exception e)
            {
                throw e;
            }

            CWrite("wait load sections element");
            WebDriverWait wait = new WebDriverWait(driver, TimeSpan.FromSeconds(timeout));

            sectionY = wait.Until<IWebElement>(d =>
                { return d.FindElement(By.Id("sections")); }
            );
            Console.Write(Environment.NewLine);
            RenderingComment();

            return driver.PageSource;

        }


        private void RenderingComment()
        {
            IWebElement commentDOM;
            try
            {
                commentDOM = driver.FindElement(By.TagName("ytd-comments"));
            }
            catch (Exception e)
            {
                throw e;
            }
            ReadOnlyCollection<IWebElement> list;
            IJavaScriptExecutor js = (IJavaScriptExecutor)driver;


            do
            {
                //리눅스 제한
                Thread.Sleep(500);


                list = commentDOM.FindElements(
                    By.TagName("ytd-comment-thread-renderer"));

                CWrite("최소치까지 불려오는 중입니다: " + (list.Count).ToString() + "개");
                MoveTo(js, getSectionEndY());


            } while (list.Count < downCount);

        }


        private void MoveTo(IJavaScriptExecutor js,int height)
        {
            js.ExecuteScript(
                    string.Format("window.scrollTo(0, {0})", height)
            );
            
        }

        private void CWrite(string msg)
        {
            Console.SetCursorPosition(left, top);
            Console.Write(msg);
        }


        private int getSectionEndY()
        {
            
            return int.Parse(sectionY.GetAttribute("offsetTop")) + sectionY.Size.Height;
        }
        
    }

}