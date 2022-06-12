# Ubisoft Toronto NEXT 2022 Programming Submission

![Mina from Watch Dogs: Legion](https://user-images.githubusercontent.com/19493797/173255638-29248c96-c3b9-41a3-a14a-a3553be84425.png)

"Ubisoft Toronto NEXT is an annual competition designed to showcase the talent of video game development students in Ontario and to help kickstart their careers in the industry." — [Official Website](https://toronto.ubisoft.com/next/)

---

This year's challenge was to make a game inspired by [Gravitar](https://en.wikipedia.org/wiki/Gravitar) in C++ using the provided API.

_Vanguard Mission Zero: Genesis Odyssey_ is my programming submission that won first place. Check out the [gameplay video](https://youtu.be/N88Oq19CvQY)!

![2022-03-14 07-20-13_Trim](https://user-images.githubusercontent.com/19493797/173255649-7b8f09fc-f140-4f83-b023-dce2e015d2ad.gif)

> Fun fact, my game was lovingly named by Stephen Vijayakumar and Abhinav Dhindsa.

## Engine features

- 3D graphics featuring particles, lighting, and backface culling ✨
- CPU-friendly component design using data locality and object pooling 🧱
- Automated unit tests and code formatting 🤖

## Running the game

Open **Game.sln** in Visual Studio 2022 and hit **F5**.

That's it!

---

## Learning resources

Here's what I personally used in order to make this submission.

### [(Free) Learn C++ by Codecademy](https://www.codecademy.com/learn/learn-c-plus-plus)

The very basics of C++. Definitely do all of this.

### [(Free) Beginning Game Programming v2.0 by Lazy Foo'](https://lazyfoo.net/tutorials/SDL/)

Make your first game using C++. I did lessons 1 to 29 inclusive which is everything you need to make a game like Pong.

### [(Free/Paid) Game Programming Patterns by Robert Nystrom](https://gameprogrammingpatterns.com/)

Take your code to the next level. The web version is free but I did buy a physical copy and it's one of my most useful reference books. I've read it front to back a few times now.

### [(Free) Code-It-Yourself! 3D Graphics Engine by Javidx9](https://youtu.be/ih20l3pJoeU)

4 part video series, but I only did the first 3 parts which covered: triangles, projection, normals, culling, lighting, object files, cameras, and clipping. These all made its way into my final rendering code in one form or another.

### [(Paid) Essential Mathematics for Games and Interactive Applications by James M. Van Verth and Lars M. Bishop](https://www.essentialmath.com/book.htm)

Inevitably, you will need to debug your graphics code. This textbook is definitely the toughest resource in this list, but it goes into _essential_ details and provides relevant examples with code snippets, as well as demo code online. Could save your life, as it did mine (pay to win?). I studied up to and including chapter 7. Using the textbook as a starting point, I built my own vector and matrix maths libraries—make sure you set aside enough time for this! I also referenced chapter 7 extensively while debugging my camera system.

> Long story short, I started studying C++ seriously starting from December 2019 until the end of February 2020.
> My schedule was based on roughly three months of ~8 hour days where I studied and made simple games in C++.
> However, I still had to prioritise and move on when I felt like I had learned what I needed to know from each resource.
> Even then, I only made 3 out of the 6 games I had originally planned to which were Pong, Breakout, and Space Invaders.
> For me, there was no realistic way to learn everything and code all the games I wanted to unless I had even more time.
