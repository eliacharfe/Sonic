target_include_directories (SFMLExamples PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_sources (SFMLExamples PRIVATE  GameManager.h
                                      Board.h
                                      GameObject.h
                                      MovingObject.h
                                      StaticObject.h

                                      Player.h
                                      Floor.h
                                      Pole.h
                                      Wall.h
                                      Ring.h
                                      Springboard.h
                                      Spikes.h
                                      HorizontalPlattform.h
                                      Emerald.h
                                      Circle.h
                                      Enemy.h
                                      EnemySlow.h
                                      EnemyFast.h
                                      VerticalPlattform.h
                                      StaticObjectConst.h
                                      StaticObjectVariable.h
                                      Boss.h
                                      Bullet.h

                                      Collision.h
                                      Direction.h
                                      
                                      Image.h
                                      Sounds.h
                                      FactoryMovable.h
                                      FactoryStatic.h
                                      Menu.h
                                     )