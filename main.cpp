#include <SFML/Graphics.hpp>
#include <math.h>
#include <sstream>
using namespace std;
using namespace sf;

#define PI 3.14159265

bool spritesChocan(Sprite sp1, Sprite sp2){
	return sp1.getGlobalBounds().intersects(sp2.getGlobalBounds());
}
	
	void setPuntaje(Text &textoPuntaje, int puntaje){
		stringstream ss;
		ss<<puntaje;
		textoPuntaje.setString(ss.str());
	}
		
		
		int main(int argc, char *argv[]){
			// crea la ventana de juego (RenderWindow)
			RenderWindow window;
			window.create(VideoMode(1920,1080),"Battle Tanks");
			sf::Vector2f windowSize(window.getView().getSize().x, window.getView().getSize().y); 
			float tankRotation = 0;
			
			window.setFramerateLimit(60);
			
			// *********** declaraciones ***********
			Texture texTank1, texBall, texWall;	// texturas
			Sprite spTank1, spBall, spWall1;		// sprites
			Font fontScore;						// fuente
			Text score1, score2,score3;				// texto de los puntajes
			
			
			
			// *********** carga de texturas, fuentes, etc ***********
			// carga las texturas
			texTank1.loadFromFile("assets/images/tank1.png");
			texBall.loadFromFile("assets/images/ball.png");
			texWall.loadFromFile("assets/images/wall.png");
			// carga la fuente
			fontScore.loadFromFile("assets/fonts/Cave-Story.ttf");
			
			
			// *********** configurar y posicionar sprites, texto, etc ***********
			// asigna las texturas a los sprites
			spTank1.setTexture(texTank1);
			spBall.setTexture(texBall);
			spWall1.setTexture(texWall);
			
			sf::Vector2f spTank1Size;
			
			spTank1Size.x =spTank1.getLocalBounds().width;
			spTank1Size.y =spTank1.getLocalBounds().height;
			
			
			//scale
			//spTank1.setScale(0.25f,0.25f);
			//		  targetSize.x / spTank1.getLocalBounds().width, 
			//		  targetSize.y / spTank1.getLocalBounds().height);
			
			spTank1.setOrigin( spTank1Size.x / 2.f, spTank1Size.y / 2.f );
			// posiciona los sprites
			spTank1.setPosition((windowSize.x/2), (windowSize.y/2));
			spBall.setPosition(100, 100);
			spWall1.setPosition(5, 5);
			
			// asigna la fuente a los textos de puntaje
			score1.setFont(fontScore);
			score2.setFont(fontScore);
			score3.setFont(fontScore);
			// posiciona los textos de los puntajes
			score1.setPosition(144, 40);
			score2.setPosition(464, 40);
			score3.setPosition(764, 40);
			// posiciona los textos de los puntajes
			score1.setFillColor(Color(250, 50, 10));
			score2.setFillColor(Color(250, 50, 10));
			score3.setFillColor(Color(250, 50, 10));
			setPuntaje(score1, 0);
			setPuntaje(score2, 0);
			setPuntaje(score3, 0);
			// *********** bucle de juego ***********
			// rapidez de la pelota
			const float BALL_VEL = 2;
			// velocidad de la pelota (componentes X e Y)
			float velBallX = BALL_VEL, velBallY = -BALL_VEL;
			// puntaje de los jugadores
			int puntajeJugador1 = 0, puntajeJugador2 = 0;
			
			// *********** bucle de juego ***********
			while(window.isOpen()) {
				Event e;
				while(window.pollEvent(e)) {
					if(e.type == Event::Closed)
						window.close();
				}
				
				// *********** mover y actualizar ***********
				// mueve la primer paleta
				if(Keyboard::isKeyPressed(Keyboard::W)  | Keyboard::isKeyPressed(Keyboard::Up)){
					
					double m,y;  
					
					if ((spTank1.getRotation() >= 0 & spTank1.getRotation() <= 90) | spTank1.getRotation() >= 270  ) {					
						m = tan ( spTank1.getRotation() * PI / 180.0 );
						y = (m*-1)+spTank1.getPosition().y;
						spTank1.move(1, spTank1.getPosition().y-y);
					} else {
						m = tan ( spTank1.getRotation() * PI / 180.0 );
						y = (m*1)+spTank1.getPosition().y;
						spTank1.move(-1, spTank1.getPosition().y-y);
					}
					score1.setString(std::to_string(spTank1.getRotation()));
					score2.setString(std::to_string(spTank1.getPosition().x));
					score3.setString(std::to_string(spTank1.getPosition().y));
					
				}
				if(Keyboard::isKeyPressed(Keyboard::S) | Keyboard::isKeyPressed(Keyboard::Down)){
					double m,y;  
					if ((spTank1.getRotation() >= 0 & spTank1.getRotation() <= 90) | spTank1.getRotation() >= 270  ) {					
						m = tan ( spTank1.getRotation() * PI / 180.0 );
						y = (m*1)+spTank1.getPosition().y;
						spTank1.move(-1, spTank1.getPosition().y-y);
					} else {
						m = tan ( spTank1.getRotation() * PI / 180.0 );
						y = (m*-1)+spTank1.getPosition().y;
						spTank1.move(1, spTank1.getPosition().y-y);
					}
					score1.setString(std::to_string(spTank1.getRotation()));
					score2.setString(std::to_string(spTank1.getPosition().x));
					score3.setString(std::to_string(spTank1.getPosition().y));
				}
				if(Keyboard::isKeyPressed(Keyboard::A)  | Keyboard::isKeyPressed(Keyboard::Left)){
					spTank1.rotate(-1.f);
					score1.setString(std::to_string(spTank1.getRotation()));
					score2.setString(std::to_string(spTank1.getPosition().x));
					score3.setString(std::to_string(spTank1.getPosition().y));
				}
				if(Keyboard::isKeyPressed(Keyboard::D)  | Keyboard::isKeyPressed(Keyboard::Right)){
					spTank1.rotate(1.f);;
					score1.setString(std::to_string(spTank1.getRotation()));
					score2.setString(std::to_string(spTank1.getPosition().x));
					score3.setString(std::to_string(spTank1.getPosition().y));
				}
				
				if(Keyboard::isKeyPressed(Keyboard::Space)){
					//calculate center of canyon
					float a,b,c;
					float A,B,C;
					double xx,yy;
					if ((spTank1.getRotation() >= 0 & spTank1.getRotation() <= 90) ) {	
						A=spTank1.getRotation();
						xx=1;
						yy=1;
					}
					if ((spTank1.getRotation() > 90 & spTank1.getRotation() <= 180) ) {	
						A=180-spTank1.getRotation();
						xx=-1;
						yy=1;
					}
					if ((spTank1.getRotation() > 180 & spTank1.getRotation() <= 270) ) {	
						A=spTank1.getRotation()-180;
						xx=-1;
						yy=-1;
					}
					if ((spTank1.getRotation() > 270) ) {	
						A=360-spTank1.getRotation();
						xx=1;
						yy=-1;
					}					
					C=90.0f;
					B=180-A-C;					
					c=spTank1Size.x/2;
					a=c*sin(A * PI / 180.0)/sin(C * PI / 180.0);
					b=a*sin(B * PI / 180.0)/sin(A * PI / 180.0);
					
					spBall.setPosition(spTank1.getPosition().x+b*xx,spTank1.getPosition().y+a*yy);
					// end of center of canyon

					// calculate bullet direction
					double m,y;  
					if ((spTank1.getRotation() >= 0 & spTank1.getRotation() <= 90) | spTank1.getRotation() >= 270  ) {					
						m = tan ( spTank1.getRotation() * PI / 180.0 );
						y = (m*1)+spTank1.getPosition().y;
						velBallX=1;
						velBallY=-1*(spTank1.getPosition().y-y);
					} else {
						m = tan ( spTank1.getRotation() * PI / 180.0 );
						y = (m*-1)+spTank1.getPosition().y;
						velBallX=-1;
						velBallY=-1*(spTank1.getPosition().y-y);
					}
					// enf of bullet dir
					
				}
				// revisa si la pelota choca con algo
				/*
				if(spritesChocan(spBall, spWall1)){
					velBallY = BALL_VEL;
				}
				*/
				
				// mueve la pelota
				spBall.move(velBallX, velBallY);
				
				// *********** dibujado ***********
				// limpia la pantalla
				window.clear(Color::White);
				// dibuja todos los sprites
				window.draw(spTank1);
				//window.draw(spWall1);
				window.draw(spBall);
				window.draw(score1);
				window.draw(score2);
				window.draw(score3);
				// refresca la pantalla
				window.display();
			}
			return 0;
		}
			
			
			
