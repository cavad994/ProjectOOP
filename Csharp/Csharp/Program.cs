using System;
using System.Numerics;
using System.Threading;


namespace Csharp
{
    class Program
    {
        public static string Questions(int index)
        {
            int[] indexlerForQuestion = new int[10] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            if (indexlerForQuestion.Length == 0)
            {
                indexlerForQuestion = new int[10] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            }
            string[] questions = new string[10];
            questions[0] = "AXC-nin yaranma tarixi :\n";
            questions[1] = "Azerbaycanin paytaxti hansi sheherdir? :\n";
            questions[2] = "Turkiyenin paytaxti hansi sheherdir? :\n";
            questions[3] = "Kurtlar vadisi seriali necenci ilde chekilmisdir? :\n";
            questions[4] = "ABS-in nece stati var? :\n";
            questions[5] = "Azerbaycanin pul vahidi hansidir? :\n";
            questions[6] = "8 ayaqli heserat hansidir? :\n";
            questions[7] = "Ingilis dilinde olan 'HELLO' nece tercume olunur? :\n";
            questions[8] = "Azerbaycan bayragi nece renglidir? :\n";
            questions[9] = "Ingilis dilinde olan 'NEVER' nece tercume olunur? :\n";


            Console.Clear();
            Answers(index);
            return questions[index];


        }

        static void Answers(int index)
        {
            int[] indexlerForAnswers = new int[10] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            string[][] answers = new string[10][];
            answers[0] = new string[3] { "1918", "1920", "1916" };
            answers[1] = new string[3] { "Baki", "Naxcivan", "Gence" };
            answers[2] = new string[3] { "Istanbul", "Ankara", "Bursa" };
            answers[3] = new string[3] { "2000", "2003", "2007" };
            answers[4] = new string[3] { "50", "40", "60" };
            answers[5] = new string[3] { "Manat", "Dollar", "Yuan" };
            answers[6] = new string[3] { "Horumcek", "Qarisqa", "Kepenek" };
            answers[7] = new string[3] { "Salam", "Sagol", "Necesen" };
            answers[8] = new string[3] { "3", "4", "5" };
            answers[9] = new string[3] { "Hec vaxt", "Hemise", "Orada" };


            int[] arr = new int[3];
            arr[0] = 99;
            arr[1] = 99;
            arr[2] = 99;
            Console.WriteLine("A - " + answers[index][NewRandomAnswer(ref arr)]);
            Console.WriteLine();
            Console.WriteLine("B - " + answers[index][NewRandomAnswer(ref arr)]);
            Console.WriteLine();
            Console.WriteLine("C - " + answers[index][NewRandomAnswer(ref arr)]);
            Console.WriteLine();
        }

        static string[] GetAnswers(int index)
        {
            string[][] answers = new string[10][];
            answers[0] = new string[3] { "1918", "1920", "1916" };
            answers[1] = new string[3] { "Baki", "Naxcivan", "Gence" };
            answers[2] = new string[3] { "Istanbul", "Ankara", "Bursa" };
            answers[3] = new string[3] { "2003", "2000", "2007" };
            answers[4] = new string[3] { "50", "40", "60" };
            answers[5] = new string[3] { "Manat", "Dollar", "Yuan" };
            answers[6] = new string[3] { "Horumcek", "Qarisqa", "Kepenek" };
            answers[7] = new string[3] { "Salam", "Sagol", "Necesen" };
            answers[8] = new string[3] { "3", "4", "5" };
            answers[9] = new string[3] { "Hec vaxt", "Hemise", "Orada" };
            return answers[index];
        }

        public static bool CorrectAnswer(string answer, int index, ref int point)
        {
            if(GetAnswers(index)[0] == answer)
            {
                Console.WriteLine();
                Console.ForegroundColor = ConsoleColor.Green;
                Console.WriteLine("\t\t\tCongratulation, your answer is true !\n");
                Thread.Sleep(2000);
                point += 1000;
                Console.ResetColor();
                return true;
            }
            else
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine("\t\t\tYou lost the game...\n\t\t\t Your score is " + point);
                Thread.Sleep(2000);
                Console.ResetColor();
                Console.WriteLine("\nIf you want to continue, press any key :\n");
                char key = Console.ReadKey().KeyChar;
                return false;
            }

        }
        public static int NewRandomAnswer(ref int[] arr)
        {
            Random rand = new Random();
        start:
            int num = rand.Next(0, 3);
            if (arr[num] == num)
            {
                goto start;
            }
            arr[num] = num;
            return num;
        }
        public static int NewRandomQuestion(ref int[] arr)
        {
            Random rand = new Random();
        start:
            int num = rand.Next(0, 10);
            if (arr[num] == num)
            {
                goto start;
            }
            arr[num] = num;
            return num;
        }

        static void start()
        {
            Console.WriteLine("Welcome to the game !\n");
            Console.WriteLine();
            while (true)
            {
                int round = 0;
                int point = 0;
                int[] arr = new int[10] { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 };
                while (round < 10)
                {
                    Console.Clear();
                    round++;
                    int questIndex = NewRandomQuestion(ref arr);
                    Console.WriteLine(round + ". " + Questions(questIndex));
                    Console.WriteLine("PLEASE ENTER FULL WORD FROM ANSWER LIKE IN A, B or C\n");
                    string answ = Console.ReadLine();
                    bool c = CorrectAnswer(answ, questIndex, ref point);
                    if (round == 10 || point == 10000)
                        for (int i = 0; i < 30; i++)
                        {
                            Console.Clear();
                            Console.ForegroundColor = ConsoleColor.Yellow;
                            Console.WriteLine("\n\n\n\n\t\t\t\t\t\tHEY, YOU WON THE GAME!\n");
                            Thread.Sleep(100);
                        }
                    else if (!c)
                        break;
                }
            }
        }
        static void Main(string[] args)
        {
            start();
        }
    }
}
