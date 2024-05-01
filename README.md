[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/2TmiRqwI)
# final-project-skeleton

    * Team Name: GMT+3
    * Team Members: Kidus Seyoum, Eleftherios Lazarinis
    * Github Repository URL: https://github.com/ese3500/final-project-gmt-3
    * Github Pages Website URL: [for final submission]
    * Description of hardware: (embedded hardware, laptop, etc) microcontroller, sensors, esp-32, shock module

## Final Project Proposal

### 1. Abstract

In a few sentences, describe your final project. This abstract will be used as the description in the evaluation survey forms.

Our project is a modern twist on the classic game of Truth or Dare, where we incorporate a lie detector to add an element of technology and excitement. The game follows the traditional rules, where players take turns choosing between answering a truth question or completing a dare. However, our version adds a technological twist.

Each participant has the opportunity to input their own questions for both truth and dare categories. These questions are then categorized accordingly and stored in the game's database. An algorithm shuffles these questions and presents them randomly to the players, ensuring a varied and unpredictable game experience.

When a player is asked a truth question, their response is not just taken at face value. Instead, the game employs a lie detector mechanism that measures the player's physiological responses, such as heart rate, sweat production, and possibly other parameters like facial expressions or voice pitch changes. These biometric indicators are analyzed in real-time to assess the likelihood of the player being truthful or deceptive in their answer.

Similarly, when a player is faced with a dare, they must complete the challenge and then answer whether they successfully completed the dare. If the player claims to have completed the dare, the lie detector is again used to verify the truthfulness of their statement.

In cases where the lie detector determines that a player has been untruthful, the game enforces a mild, safe electric shock as a penalty. This adds an element of risk and encourages players to be honest. Additionally, a servo mechanism is employed to visually indicate the result of the lie detector's analysis. The servo has two positions labeled "TRUTH" and "LIE," and it points to the corresponding label based on whether the player's answer is deemed truthful or deceptive.

Our Truth or Dare game with a lie detector aims to enhance the traditional gameplay with technology, making it more engaging and adding a layer of accountability for the players. It's a perfect blend of classic entertainment and modern innovation.

### 2. Motivation

What is the problem that you are trying to solve? Why is this project interesting? What is the intended purpose?

The goal of our project is to enhance the classic game of Truth or Dare by incorporating a lie detector, ensuring accountability and adding an element of technology-driven excitement. This idea addresses the issue of players potentially lying or not completing dares without consequences, which can diminish the game's thrill. By integrating a lie detector that analyzes physiological responses, we aim to make the game more engaging and truthful. Our project demonstrates how technology can modernize traditional social games, making them more interactive and enjoyable for participants.

### 3. Goals

These are to help guide and direct your progress.

Enhance Player Accountability

Integrate Technology

Improve Game Engagement

Ensure Safety and Ethics

User-Friendly Interface

Reliability and Accuracy

### 4. Software Requirements Specification (SRS)

Formulate key software requirements here.

-Question Randomization Algorithm: The questions are chosen randomly
-Display of the questions, and game mode on an LCD screen
-Lie Detection: Analyze biometric data coming from the heart rate sensor to assess the truthfulness of responses.
-Result Display: Show the lie detector's verdict via the servo monitor
-Penalty Enforcement: We will have a buzzer with an awful sound when theres a lie

### 5. Hardware Requirements Specification (HRS)

Formulate key hardware requirements here.

-Heart rate monitor: To record changes in heart rate during the game.
-LCD Screen: ST7735
-Buzzer: As a punishment when someone is lying
-Servo motor: To indicate the result (Truth or Lie) visually by moving a pointer or indicator.
-Buttons to change the mode (TRUTH or DARE) and move on to the next player

### 6. MVP Demo

What do you expect to accomplish by the first milestone?

We hope that the lie detector would be fully functional. 

### 7. Final Demo

What do you expect to achieve by the final demonstration or after milestone 1?

The truth or dare game, with most (hopefully all) of the features of the game, both on the software side but also on the hardware side.

### 8. Methodology

What is your approach to the problem?

We first analyzed the requirements for the project and figured out how we could best tackle the problem in an interesting and innovative way. After we decided on the prject we were analyzing the requirements for the game and the lie detector, ensuring we understand the key features and functionalities needed. We will then select and integrat the appropriate hardware, including biometric sensors for lie detection and mechanisms for the penalty system. The software development phase will involve creating the lie detection algorithm, randomizing questions, and designing a user-friendly interface. We follow an iterative process of prototyping, testing, and refining based on feedback to enhance the game's performance and user experience. Finally, we conduct extensive testing to validate the game's accuracy and safety before launching it and collecting user feedback for ongoing improvements.

### 9. Components

What major components do you need and why?
-Microcontroller
-Servo Motor
-Heart Rate Monitor
-GSR Monitor
-Electric Shock Module
-Screen

### 10. Evaluation

What is your metric for evaluating how well your product/solution solves the problem? Think critically on this section. Having a boolean metric such as “it works” is not very useful. This is akin to making a speaker and if it emits sound, albeit however terrible and ear wrenching, declare this a success.
It is recommended that your project be something that you can take pride in. Oftentimes in interviews, you will be asked to talk about projects you have worked on.

To evaluate the effectiveness of our Truth or Dare game with a lie detector, we need to consider several metrics beyond a simple "it works" assessment. Those are specified below:

-Lie Detector Accuracy: Measure the percentage of correct detections
-User Satisfaction: test it on users and assess their satisfaction with the game interface, ease of use and overall enjoyment
-Safety of the electric shock module: Ensure that we uphold safety standards
-Technical Performance: Ensure that the response time, battery life, reliability are at a high level

By evaluating these metrics, we can determine the success of the Truth or Dare game with a lie detector in providing an accurate, safe, enjoyable, and engaging experience for players. This comprehensive evaluation approach ensures that the project is something we can take pride in and confidently discuss in interviews or other professional contexts.

### 11. Timeline

This section is to help guide your progress over the next few weeks. Feel free to adjust and edit the table below to something that would be useful to you. Really think about what you want to accomplish by the first milestone.

| **Week**            | **Task**          | **Assigned To**    |
|----------           |---------          |------------------- |
| Week 1: 3/24 - 3/31 |Component Search/ Order|Both                    |
| Week 2: 4/1 - 4/7   |Code for Lie Detector     |    Both                |
| Week 3: 4/8 - 4/14  |Code for software          |     Both               |
| Week 4: 4/15 - 4/21 |Assembling hardware/Testing lie detector         |   Both                 |
| Week 5: 4/22 - 4/26 |Putting it all together/ Debugging & Improving the code for everything         | Both+                   |

### 12. Proposal Presentation

Add your slides to the Final Project Proposal slide deck in the Google Drive.
https://docs.google.com/presentation/d/1POS2FrLU4fazUkQQjPzKI0OL3KIg7X1V2p2VRbRrQFw/edit?usp=sharing

## Final Project Report

Don't forget to make the GitHub pages public website!
If you’ve never made a Github pages website before, you can follow this webpage (though, substitute your final project repository for the Github username one in the quickstart guide):  <https://docs.github.com/en/pages/quickstart>

### 1. Video
https://drive.google.com/file/d/1CXbteqhHgOuDSwedZIaaMVsTIeWjQJRV/view?usp=sharing


### 2. Images

Glove with Atmega328pb AVR xplained board attached to it along with the heart rate monitor:

![IMG_0606](https://github.com/ese3500/final-project-gmt-3/assets/120141948/1173bdac-541b-4fc4-839f-b7a231f207a2)

The game box with two bottons one to switch modes and another to go to the next question. Including a monitor to display the state of the game such as the current mode and question. It also includes a servo and buzzer as a way to indicate truth or lie.

![IMG_0605](https://github.com/ese3500/final-project-gmt-3/assets/120141948/9f6965c7-e5ce-4302-bbae-90e034043467)



### 3. Results

What were your results? Namely, what was the final solution/design to your problem?

#### 3.1 Software Requirements Specification (SRS) Results

Based on your quantified system performance, comment on how you achieved or fell short of your expected software requirements. You should be quantifying this, using measurement tools to collect data.
-Storing Questions: We have 2 arrays which store truth and lie questions. Whenever a truth question is requested to be displayed we access the truth array and whenever a dare question is requested we access the dare array. This is testable by the questions that are displayed and we could differentiate by seeing if the question we got was actually a truth or a dare question.
-Randomizing Questions: We are using the built-in c rand() function to pick random questions each time that a question is being requested. We had to adjust it to only give integer answers between 0 and array.length-1. This was also testable during the display, since the questions were well shuffled and we were not getting the same few questions over and over but we had a wide variety of questions.
-Displaying Game Mode: The display of the game mode happens each time that the MODE button is pressed. Each time that this button is pressed we have a variable that increments itself and even numbers correspond to truth mode and odd numbers correspond to dare mode. Then depending on which mode we are in, we use the LCD screen library to display it. This was tested by seeing the successful switch between TRUTH and DARE on the LCD screen each time that the MODE button is pressed. 
-Displaying Questions: The display of the questions is happening when the user is requesting a new question. That happens by reading the input of the NEXT QUESTION button (as specified in the HRS) which when the button is pressed we set a variable to 1 meaning that the user has requested a new question. Then based on the game mode variable and the question randomization, we pick a random question, clear the screen from the previous question and display it on the screen. This was testable by the LCD screen output where we 
-LCD Screen Library: We used the same graphics library that we created on lab 4, since we are using the same LCD screen and the library could handle our display requirements. We were able to test the outputs by seeing that it displays the game mode and question correctly.
-Lie Detection:
-Serial/Wired Communication:
-Heart Beat Analysis:
-Result Display: The result display happened by receiving a T or L via the serial communication and then based on that we power up the buzzer and make the servo motor turn to either Liar or Squealer depending on the outcome. We were able to test that by seeing the inputs of the serial communication in the data visualizer and based on that see if the buzzer should buzz, and where the servo motor should be pointing and they were both functioning as expected.
-Penalty Enforcement: When we received an L from the serial communication, we turned the buzzer on, emitting a loud and annoying sound, which was verified by other people to be annoying, so we tested it that way.


#### 3.2 Hardware Requirements Specification (HRS) Results

Based on your quantified system performance, comment on how you achieved or fell short of your expected hardware requirements. You should be quantifying this, using measurement tools to collect data.

### 4. Conclusion

Reflect on your project. Some questions to consider: What did you learn from it? What went well? What accomplishments are you proud of? What did you learn/gain from this experience? Did you have to change your approach? What could have been done differently? Did you encounter obstacles that you didn’t anticipate? What could be a next step for this project?

## References

Fill in your references here as you work on your proposal and final submission. Describe any libraries used here.

## Github Repo Submission Resources

You can remove this section if you don't need these references.

* [ESE5160 Example Repo Submission](https://github.com/ese5160/example-repository-submission)
* [Markdown Guide: Basic Syntax](https://www.markdownguide.org/basic-syntax/)
* [Adobe free video to gif converter](https://www.adobe.com/express/feature/video/convert/video-to-gif)
* [Curated list of example READMEs](https://github.com/matiassingers/awesome-readme)
* [VS Code](https://code.visualstudio.com/) is heavily recommended to develop code and handle Git commits
  * Code formatting and extension recommendation files come with this repository.
  * Ctrl+Shift+V will render the README.md (maybe not the images though)
