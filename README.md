## Sonic
Object  Oriented Project Game (C++)


Project OOP2 

אלישר פייג 302278338 
שגיא אביטל 305295826

הסבר כללי:

מימוש המשחק Sonic

סוניק הוא משחק פלטפורמה בו השחקן אינו יכול לחזור אחורה. המשחק מבוסס על מהירות ,
 בעל מפה גדולה יותר מן המוצג. על השחקן לעבור סדרת מכשולים ואויבים תוך שימוש בכללי
 פיזיקה ומטרתו להגיע לצד השני של המפה, ובכך לעבור שלב. לשחקן אפשרות לקפוץ, לרוץ 
ימינה, ולהשתמש בכוח הגלגול שלו (היכולת להפוך לצורת כדור ולהתגלגל במהירות גבוהה מאוד 
על כל משטח והתעלם מחלק מחוקי הפיזיקה, כאשר הוא מתנגש באויב הוא הורג אותו או מוריד
 לו חיים, או להתגלגל על פני משטחים מאונכים לרצפה ולא ניזוק מדוקרנים). השחקן מתחיל
 עם 3 לבבות כאשר כל לב מייצג חיים שלמים, כאשר שחקן ניזוק הוא יכול לאבד חלק מן החיים
 (להפצע) או לגמרי לאבד לב. כאשר השחקן במצב התגלגלות הוא יכול לנוע שמאלה גם.
בסוף כל שלב השחקן אוסף יהלום אשר מקנה לו את הזכות לעבור שלב אך הוא יכול לאוספו
רק לאחר שהוא מביס את הבוס, (כאשר הוא מוריד לבוס את כל בר החיים תוך שימוש בכוח
 ההתגלגלות).
מוצג למשתמש הניקוד (כמות טבעות), החיים, הלבבות, היהלומים והזמן

 במשחק יש מקפצות, דוקרנים, מוטות, קירות, רצפה, טבעות, אויבים ופלטפורמות הנעות באוויר
(אופקיות ואנכיות), מקפצות, בורות

דוקרנים ^: ממוקם ברצפות ומוריד חיים לשחקן בעת הוא מתנגש בהם. ניתן להתחמק מהם
 או ע"י קפיצה מעליהם או ע"י שימוש בכוח הכדור (התגלגלות)
מוטות - : השחקן יכול לתפס עליהם, לנוע עליהם ימינה או לקפוץ מהם כלפי מטה.
קירות # : מכשול סטטי שהשחקן אינו יכול לעבור.
רצפה F: קיר אופקי.
פלטפורמות הנעות באוויר = / V: מכשול דינמי הנע אופקי/אנכי וניתן לתפס עליו 
עיגולים O: עליהם הוא נע באופן מעגלי (עיגולים גדולים שהוא רץ עליהם)
טבעות o: השחקן יכול לאסוף מטבעות, וכמות החיים  מושפעת ע"י כמות הטבעות שהשחקן אוסף. 
כאשר הוא אוסף 50 טבעות ובר החיים שלו מלא הוא מקבל לב (עד ל6 במקסימום.)
אויבים & / S : מורדים חיים לשחקן בעת התנגשות (ע"פ מהירות האויב) אלא אם כן השחקן מתגלגל 
בוס B: מוריד לשחקן חיים באמצעות יריות (עצמת ההורדה משתנה בהתאם לשלב וכן מהירות הכדורים)
אם השחקן נפגש עם הבוס יורד לו לב אלא אם כן הוא במצב כדור, במקרה כזה השחקן מוריד 
לבוס 10 מהחיים
כדורים (יריות) *: הבוס יורה אותם כשהשחקן בטווח ועוקבות אחר השחקן במידת מה ונעלמות
כאשר מתנגשות באובייקטי המשחק
מקפצות u: מקפיצות את השחקן לגובה רב
בורות ' ': ממוקמות בין רצפות, כאשר השחקן נופל לבור הוא מת

המשתמש, נע באמצעות החצים כאשר למעלה זה קפיצה, לחיצה על רווח השחקן עובר להתגלגל

מטרת המשחק-
להגיע ליהלום ולהרוג את הבוס תוך התחמקות מהמכשולים שבדרך ואסיפת מקסימום של טבעות
אלא מקנים לו חיים ובכך עוזרות לו בשלב

 תיכון (Desing):

המשחק מנוהל ע"י GameMangaer בשיתוף עם Menu ועם Board
המשחק מחולק למחלקות הבאות:

GameMangaer
Board
Image (Singleton)
Sounds (Singleton)
Utilities.h
Cons.h
Collision (multi-method)
Location
Direction
Rotation
Exception
GameObject <|-- StaticObject
GameObject <|-- MovingObject
StaticObject <|-- StaticObjectConst
StaticObject <|-- StaticObjectVariable
StaticObject <|-- FactoryStatic
StaticObjectConst <|-- Pole
StaticObjectConst <|-- Wall
StaticObjectConst <|-- Spikes
StaticObjectConst <|-- Springboard
StaticObjectConst <|-- Floor
StaticObjectConst <|-- Circle
StaticObjectVariable <|-- Emerald
StaticObjectVariable <|-- Ring
MovingObject <|-- Player
MovingObject <|-- Enemy
MovingObject <|-- HorizontalPlattform
MovingObject <|-- VerticalPlattform
MovingObject <|--Bullet
MovingObject <|--FactoryMovable
Enemy <|-- EnemySlow
Enemy <|-- EnemyFast
Enemy <|-- Boss

מבני נתונים:

בBoard:
	vector < string > m_charBoard;
	vector < shared_ptr < MovingObject >> m_movables;
	vector < unique_ptr < StaticObject >> m_statics;

	vector < unique_ptr < GameObject >> m_menuObjects; // for creator level mode
	vector < unique_ptr < GameObject >> m_objects; // for creator level mode

בMenu:
map < Bool, bool > m_mapBool;

בSounds מחלקת singleton :
	map < TypeSound, sf::SoundBuffer > m_mapSoundBuffer;
	map < TypeSound, sf::Sound > m_mapSounds;
	map< TypeMusic, sf::Music > m_mapMusic;

ב Image מחלקת singleton ::
map< TypeImage, sf::Texture > m_mapTexture;
	map< TypeImage, sf::Sprite > m_mapSprite;

ב Collision (מולטי-מטוד):
std::map<Key, HitFunctionPtr>;



Methods used: 
•	Inheritance and Polymorphism
•	Smart pointers
•	Multi-Methods
•	Singletons
•	Design patterns, Factories
•	Iterators
•	Exceptions
•	Move-semantics
•	Sprite Sheets, map and more


פורמט הקובץ:

Board.txt
מדובר בקובץ בודד, כל שלב מופרד מהשלב האחר בשורה ריקה. לא נדרשות פעולות 
בין כל שלב (שומר בכל שלב את המיקום הנוכחי של תחילת השלב למקרה של פסילה,
ובמקרה של ניצחון אוכל את השורה הריקה ומתקדם לייצוג של השלב הבא ושומר באותו
אופן את תחילת השלב הנוכחי וכך הלאה.)

תוספות: יש אופציה לבניית השלב ושיחוק בו, וכן כפתורים נוחים לשימוש המשתמש כגון "פאוס",
להנמיך/לכבות את המוסיקה, מעבר לחלונות אחרים וכדומה

אלגוריתמים הראויים לציון:
**********************************************************
ירושה ופולימורפיזם, מצביעים חכמים, טיפול בחריגות, מולטי-מטוד לטיפול בהתנגשויות
 , Factory ליצירת האובייקטים, Sprite Sheet , שימושים של map לצורך טעינות וצריכים שונים,
 move semantics , Singleton, מעבר על איטרוטורים ברנג' פור לופ וכו',
***********************************************************

באגים ידועים:
אין
