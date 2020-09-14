using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.IO;
using TriangleCheck;

namespace TriangleTest
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void TestMethod1()
        {
            string outputPath = "../../../output.txt";
            File.WriteAllText(outputPath, string.Empty);
            using StreamWriter output = new StreamWriter(outputPath, true);

            using (var inputFile = new StreamReader("../../../input.txt"))
            {
                int testCounter = 1;
                string argsLine;
                while((argsLine = inputFile.ReadLine()) != null)
                {
                    string expectedResult = inputFile.ReadLine();
                    var sw = new StringWriter();
                    Console.SetOut(sw);
                    Program.Main(argsLine.Split(" "));
                    string result = sw.ToString().Replace("\r\n", "");

                    if(result == expectedResult)
                    {
                        output.WriteLine("Tets " + testCounter + ": success");
                    }
                    else 
                    {
                        output.WriteLine("Test " + testCounter + ": error");
                    }

                    Assert.AreEqual(result, expectedResult);

                    testCounter++;
                }
            }
        }
    }
}
