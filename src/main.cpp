#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <FluxGarage_RoboEyes.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

RoboEyes<Adafruit_SSD1306> roboEyes(display);


// =====================================================
// AIVI EMOTIONS
// =====================================================

enum AiviEmotion {
  EM_NORMAL,
  EM_HAPPY,
  EM_ANGRY,
  EM_SAD,
  EM_LOVE,
  EM_KISS,
  EM_SHY,
  EM_SIDE_EYE,
  EM_SURPRISED,
  EM_THINKING,
  EM_SLEEPY,
  EM_CONFUSED,
  EM_EXCITED
};

AiviEmotion currentEmotion = EM_NORMAL;


// =====================================================
// ANIMATION VARIABLES
// =====================================================

unsigned long animationTimer = 0;
unsigned long demoTimer = 0;
unsigned long sleepTimer = 0;

int thinkingDots = 0;
int sleepStage = 0;
int demoIndex = 0;

bool demoMode = false;


// =====================================================
// RESET ROBOEYES
// =====================================================

void resetEyes() {

  roboEyes.setMood(DEFAULT);

  roboEyes.setPosition(DEFAULT);

  roboEyes.setCuriosity(OFF);

  roboEyes.setHFlicker(OFF);

  roboEyes.setVFlicker(OFF);

  roboEyes.setIdleMode(ON, 2, 2);

  roboEyes.setAutoblinker(ON, 3, 2);
}


// =====================================================
// NORMAL
// =====================================================

void normalEyes() {

  resetEyes();

  roboEyes.setMood(DEFAULT);
  roboEyes.setPosition(DEFAULT);
  roboEyes.setIdleMode(ON, 2, 2);
}


// =====================================================
// HAPPY
// =====================================================

void happyEyes() {

  resetEyes();

  roboEyes.setMood(HAPPY);
  roboEyes.setPosition(DEFAULT);
  roboEyes.setIdleMode(ON, 2, 2);

  roboEyes.setAutoblinker(ON, 3, 2);
}


// =====================================================
// ANGRY
// KEEP EXACTLY AS BEFORE
// =====================================================

void angryEyes() {

  resetEyes();

  roboEyes.setMood(ANGRY);

  roboEyes.setPosition(DEFAULT);

  roboEyes.setIdleMode(OFF);

  roboEyes.setAutoblinker(ON, 2, 1);
}


// =====================================================
// SAD
// KEEP EXACTLY AS BEFORE
// =====================================================

void sadEyes() {

  resetEyes();

  roboEyes.setMood(TIRED);

  roboEyes.setPosition(S);

  roboEyes.setIdleMode(OFF);

  roboEyes.setAutoblinker(ON, 5, 2);
}


// =====================================================
// LOVE
// KEEP EXACTLY AS BEFORE
// =====================================================

void loveEyes() {

  resetEyes();

  roboEyes.setMood(HAPPY);

  roboEyes.setPosition(DEFAULT);

  roboEyes.setIdleMode(OFF);

  roboEyes.setAutoblinker(ON, 5, 2);
}


// =====================================================
// KISS
// =====================================================

void kissEyes() {

  resetEyes();

  // Keep the eyes soft and slightly playful
  roboEyes.setMood(HAPPY);

  roboEyes.setPosition(DEFAULT);

  roboEyes.setIdleMode(OFF);

  roboEyes.setAutoblinker(ON, 3, 1);
}


// =====================================================
// SHY
// =====================================================

void shyEyes() {

  resetEyes();

  roboEyes.setMood(HAPPY);

  roboEyes.setPosition(SE);

  roboEyes.setIdleMode(OFF);

  roboEyes.setAutoblinker(ON, 2, 1);
}


// =====================================================
// SIDE EYE
// KEEP EXACTLY AS BEFORE
// =====================================================

void sideEye() {

  resetEyes();

  roboEyes.setMood(DEFAULT);

  roboEyes.setPosition(E);

  roboEyes.setCuriosity(ON);

  roboEyes.setIdleMode(OFF);

  roboEyes.setAutoblinker(ON, 4, 1);
}


// =====================================================
// SURPRISED
// =====================================================

void surprisedEyes() {

  resetEyes();

  roboEyes.setMood(DEFAULT);

  roboEyes.setPosition(DEFAULT);

  roboEyes.setCuriosity(ON);

  roboEyes.setIdleMode(OFF);

  roboEyes.setAutoblinker(ON, 6, 1);
}


// =====================================================
// THINKING
// =====================================================

void thinkingEyes() {

  resetEyes();

  roboEyes.setMood(DEFAULT);

  roboEyes.setPosition(NW);

  roboEyes.setIdleMode(OFF);

  roboEyes.setAutoblinker(ON, 4, 2);
}


// =====================================================
// SLEEPY
// =====================================================

void sleepyEyes() {

  resetEyes();

  // Start the sleepy animation with fully open eyes.
  // The updateSleepAnimation() function gradually closes them.
  roboEyes.setMood(DEFAULT);
  roboEyes.setPosition(S);
  roboEyes.setIdleMode(OFF);
  roboEyes.setAutoblinker(OFF);

  // Restore RoboEyes' normal eye size before the sequence starts.
  roboEyes.setHeight(36, 36);

  sleepStage = 0;
  sleepTimer = millis();
}


// =====================================================
// CONFUSED
// =====================================================

void confusedEyes() {

  resetEyes();

  roboEyes.setMood(DEFAULT);

  // Look upward
  roboEyes.setPosition(N);

  roboEyes.setIdleMode(OFF);

  roboEyes.setAutoblinker(ON, 4, 2);
}


// =====================================================
// EXCITED
// =====================================================

void excitedEyes() {

  resetEyes();

  roboEyes.setMood(HAPPY);

  roboEyes.setPosition(DEFAULT);

  roboEyes.setIdleMode(ON, 1, 1);

  roboEyes.setAutoblinker(ON, 2, 1);

  roboEyes.anim_laugh();
}


// =====================================================
// KISS GRAPHIC
// =====================================================

void drawKissGraphic() {

  // Larger puckered lips at the bottom center

  int x = 64;
  int y = 48;

  // Upper lip
  display.drawLine(x - 10, y,     x - 4, y - 5, WHITE);
  display.drawLine(x - 4,  y - 5, x,     y - 1, WHITE);
  display.drawLine(x,      y - 1, x + 4, y - 5, WHITE);
  display.drawLine(x + 4,  y - 5, x + 10, y, WHITE);

  // Lower lip
  display.drawLine(x - 10, y,     x - 5, y + 5, WHITE);
  display.drawLine(x - 5,  y + 5, x,     y + 6, WHITE);
  display.drawLine(x,      y + 6, x + 5,  y + 5, WHITE);
  display.drawLine(x + 5,  y + 5, x + 10, y, WHITE);

  // Inner lip line
  display.drawLine(x - 6, y, x + 6, y, WHITE);
}


// =====================================================
// SHY / BLUSH
// =====================================================

void drawBlush() {

  // Shy blush:
  // small vertical strokes at the upper-left
  // side of the LEFT eye only.

  display.drawLine(18, 35, 18, 40, WHITE);
  display.drawLine(22, 34, 22, 39, WHITE);

}
  // Extra pixels to make the blush feel denser
  


// =====================================================
// SURPRISE O
// =====================================================

void drawSurpriseMouth() {

  // Small O underneath the eyes

  display.drawCircle(
    64,
    53,
    5,
    WHITE
  );
}


// =====================================================
// THINKING DOTS
// =====================================================

void drawThinkingDots() {

  int y = 54;

  // Animated loading chain
  // .  ..  ...

  if (thinkingDots >= 1)
    display.fillCircle(54, y, 2, WHITE);

  if (thinkingDots >= 2)
    display.fillCircle(64, y, 2, WHITE);

  if (thinkingDots >= 3)
    display.fillCircle(74, y, 2, WHITE);
}


// =====================================================
// SLEEP ZZZ
// =====================================================

void drawSleepZZ() {

  // Show Zs only during:
  // Stage 1 = half closed
  // Stage 2 = almost closed
  // Stage 3 = fully closed
  // Hide them during reopening stages 4, 5, 6.

  if (sleepStage < 1 || sleepStage > 3)
    return;

  display.setTextColor(WHITE);
  display.setTextSize(1);

  // Small Z
  display.setCursor(107, 20);
  display.print("Z");

  // Large Z
  display.setCursor(118, 12);
  display.print("Z");
}

// =====================================================
// CONFUSED QUESTION MARK
// =====================================================

void drawQuestionMark() {

  // Strong, clearly visible question mark
  // positioned BELOW the eyes.

  display.setTextColor(WHITE);

  display.setTextSize(2);

  display.setCursor(94, 45);

  display.print("?");

  display.setTextSize(1);

  // Extra dot underneath for stronger visual weight
  display.fillCircle(101, 60, 1, WHITE);
}


// =====================================================
// DRAW CUSTOM EMOTION ELEMENTS
// =====================================================

void drawEmotionGraphics() {

  switch (currentEmotion) {

    case EM_KISS:
      drawKissGraphic();
      break;

    case EM_SHY:
      drawBlush();
      break;

    case EM_SURPRISED:
      drawSurpriseMouth();
      break;

    case EM_THINKING:
      drawThinkingDots();
      break;

    case EM_SLEEPY:
      drawSleepZZ();
      break;

    case EM_CONFUSED:
      drawQuestionMark();
      break;

    default:
      break;
  }
}


// =====================================================
// ANIMATION UPDATE
// =====================================================

void updateEmotionAnimation() {

  unsigned long now = millis();

  // -----------------------------------------------
  // Thinking loading dots
  // -----------------------------------------------

  if (currentEmotion == EM_THINKING) {

    if (now - animationTimer >= 450) {

      animationTimer = now;

      thinkingDots++;

      if (thinkingDots > 3)
        thinkingDots = 0;
    }
  }

  else {

    thinkingDots = 0;
  }
}


// =====================================================
// SLEEP ANIMATION
// =====================================================

void updateSleepAnimation() {

  if (currentEmotion != EM_SLEEPY) {
    sleepStage = 0;
    return;
  }

  unsigned long now = millis();

  // Move through: open -> half -> almost closed -> closed
  // -> almost closed -> half -> open.
  if (now - sleepTimer < 900)
    return;

  sleepTimer = now;

  sleepStage++;

  if (sleepStage > 6)
    sleepStage = 0;

  switch (sleepStage) {

    case 0:
      roboEyes.setHeight(36, 36);   // fully open
      break;

    case 1:
      roboEyes.setHeight(22, 22);   // half closed -> ZZZ appears
      break;

    case 2:
      roboEyes.setHeight(12, 12);   // almost closed
      break;

    case 3:
      roboEyes.setHeight(1, 1);     // fully closed
      break;

    case 4:
      roboEyes.setHeight(12, 12);   // slowly opening
      break;

    case 5:
      roboEyes.setHeight(22, 22);   // half open
      break;

    case 6:
      roboEyes.setHeight(36, 36);   // fully open
      break;
  }
}


// =====================================================
// SET EMOTION
// =====================================================

void setEmotion(AiviEmotion newEmotion) {

  currentEmotion = newEmotion;

  demoMode = false;

  animationTimer = millis();

  thinkingDots = 0;

  switch (currentEmotion) {

    case EM_NORMAL:

      normalEyes();

      Serial.println("NORMAL");

      break;


    case EM_HAPPY:

      happyEyes();

      Serial.println("HAPPY");

      break;


    case EM_ANGRY:

      angryEyes();

      Serial.println("ANGRY");

      break;


    case EM_SAD:

      sadEyes();

      Serial.println("SAD");

      break;


    case EM_LOVE:

      loveEyes();

      Serial.println("LOVE");

      break;


    case EM_KISS:

      kissEyes();

      Serial.println("KISS");

      break;


    case EM_SHY:

      shyEyes();

      Serial.println("SHY");

      break;


    case EM_SIDE_EYE:

      sideEye();

      Serial.println("SIDE EYE");

      break;


    case EM_SURPRISED:

      surprisedEyes();

      Serial.println("SURPRISED");

      break;


    case EM_THINKING:

      thinkingEyes();

      Serial.println("THINKING");

      break;


    case EM_SLEEPY:

      sleepyEyes();

      sleepStage = 0;
      sleepTimer = millis();

      Serial.println("SLEEPY");

      break;


    case EM_CONFUSED:

      confusedEyes();

      Serial.println("CONFUSED");

      break;


    case EM_EXCITED:

      excitedEyes();

      Serial.println("EXCITED");

      break;
  }
}


// =====================================================
// SERIAL COMMANDS
// =====================================================

void handleSerial() {

  if (!Serial.available())
    return;

  char command = Serial.read();

  switch (command) {

    case 'N':
    case 'n':
      setEmotion(EM_NORMAL);
      break;


    case 'H':
    case 'h':
      setEmotion(EM_HAPPY);
      break;


    case 'A':
    case 'a':
      setEmotion(EM_ANGRY);
      break;


    case 'S':
    case 's':
      setEmotion(EM_SAD);
      break;


    case 'L':
    case 'l':
      setEmotion(EM_LOVE);
      break;


    case 'K':
    case 'k':
      setEmotion(EM_KISS);
      break;


    case 'Y':
    case 'y':
      setEmotion(EM_SHY);
      break;


    case 'E':
    case 'e':
      setEmotion(EM_SIDE_EYE);
      break;


    case 'U':
    case 'u':
      setEmotion(EM_SURPRISED);
      break;


    case 'T':
    case 't':
      setEmotion(EM_THINKING);
      break;


    case 'D':
    case 'd':
      setEmotion(EM_SLEEPY);
      break;


    case 'F':
    case 'f':
      setEmotion(EM_CONFUSED);
      break;


    case 'X':
    case 'x':
      setEmotion(EM_EXCITED);
      break;


    case '0':

      demoMode = true;

      demoIndex = 0;

      demoTimer = millis() - 4000;

      break;
  }
}


// =====================================================
// DEMO
// =====================================================

void runDemo() {

  if (!demoMode)
    return;

  if (millis() - demoTimer < 3500)
    return;

  demoTimer = millis();

  switch (demoIndex) {

    case 0:
      setEmotion(EM_NORMAL);
      break;

    case 1:
      setEmotion(EM_HAPPY);
      break;

    case 2:
      setEmotion(EM_LOVE);
      break;

    case 3:
      setEmotion(EM_KISS);
      break;

    case 4:
      setEmotion(EM_SHY);
      break;

    case 5:
      setEmotion(EM_SIDE_EYE);
      break;

    case 6:
      setEmotion(EM_ANGRY);
      break;

    case 7:
      setEmotion(EM_SAD);
      break;

    case 8:
      setEmotion(EM_THINKING);
      break;

    case 9:
      setEmotion(EM_CONFUSED);
      break;

    case 10:
      setEmotion(EM_SURPRISED);
      break;

    case 11:
      setEmotion(EM_EXCITED);
      break;

    case 12:
      setEmotion(EM_SLEEPY);
      break;
  }

  demoIndex++;

  if (demoIndex > 12)
    demoIndex = 0;
}


// =====================================================
// SETUP
// =====================================================

void setup() {

  Serial.begin(115200);

  Wire.begin(21, 22);

  if (!display.begin(
        SSD1306_SWITCHCAPVCC,
        OLED_ADDR)) {

    Serial.println("SSD1306 FAILED");

    while (true);
  }

  roboEyes.begin(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    100
  );

  setEmotion(EM_NORMAL);

  Serial.println();
  Serial.println("==============================");
  Serial.println("       AIVI EYES V3");
  Serial.println("==============================");
  Serial.println("N = Normal");
  Serial.println("H = Happy");
  Serial.println("A = Angry");
  Serial.println("S = Sad");
  Serial.println("L = Love");
  Serial.println("K = Kiss");
  Serial.println("Y = Shy");
  Serial.println("E = Side Eye");
  Serial.println("U = Surprised");
  Serial.println("T = Thinking");
  Serial.println("D = Sleepy");
  Serial.println("F = Confused");
  Serial.println("X = Excited");
  Serial.println("0 = Demo");
  Serial.println("==============================");
}


// =====================================================
// LOOP
// =====================================================

void loop() {

  // RoboEyes must update continuously
  roboEyes.update();

  // Process commands
  handleSerial();

  // Update emotion-specific animation
  updateEmotionAnimation();

  // Update only the sleepy open/close sequence
  updateSleepAnimation();

  // Add our small supporting graphics
  drawEmotionGraphics();

  // Show final frame
  display.display();
}