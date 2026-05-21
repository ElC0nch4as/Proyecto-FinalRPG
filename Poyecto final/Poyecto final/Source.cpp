// NOMENCLATURA UTILIZADA EN EL CODIGO
// 1) camelCase:
//    Se usa en nombres de variables, atributos y metodos.
//    Ejemplosss: vidaMaxima, buffCampamentoActivo, mostrarInventario, usarPoushonEnCombate.
//
// 2) snake_case
//    Se usa en parametros recibidos por constructores o funciones para diferenciarlos
//    de los atributos internos del objeto.
//    Ejemplos: param_nombre, param_vida, param_danio.

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <conio.h>

#define NOMINMAX // Esto es para evitar conflicto con el windows.h ya que define min y max como macros y eso me rompia el codigo

#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

// Esta funcion centra un texto dentro de un ancho fijo.
// Se usa para acomodar visualmente el estante de la tienda.
std::string centrarTexto(std::string texto, int ancho) {
	// Si el texto ya mide igual o mas que el ancho pedido, se devuelve tal cual.
	if (texto.size() >= ancho) {
		return texto;
	}

	// Se calculan los espacios necesarios a izquierda y derecha
	// para que el texto quede centrado.
	int espaciosIzquierda = (ancho - texto.size()) / 2;
	int espaciosDerecha = ancho - texto.size() - espaciosIzquierda;

	// Se devuelve el texto con espacios agregados a ambos lados.
	return std::string(espaciosIzquierda, ' ') + texto + std::string(espaciosDerecha, ' ');
}

// Esta funcion pide un numero al usuario y valida que de verdad sea numerico.
// Se usa en menus y selecciones del sistema.
int pedirNumero(std::string mensaje) {
	int numero;

	// Se muestra el mensaje que indica que numero debe escribir el usuario.
	std::cout << std::endl;
	std::cout << mensaje << std::endl;

	// Este while sirve para repetir la lectura hasta que el usuario
	// escriba un numero valido.
	while (!(std::cin >> numero)) {
		std::cout << "Error. Ingrese solo numeros." << std::endl;

		// Se limpia el estado de error de cin.
		std::cin.clear();

		// Se ignora la entrada incorrecta restante para evitar bucles infinitos.
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	// Se limpia el salto de linea sobrante del buffer.
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return numero;
}

// Clase que representa un item del juego.
// En este avance se usa sobre todo para el inventario y la tienda.
class Item {
	std::string nombre;
	std::string tipo;
	int valor;
	int precio;
	int cantidad;
	bool secreto;

public:
	// Constructor del item.
	Item(std::string param_nombre, std::string param_tipo, int param_valor, int param_precio, int param_cantidad, bool param_secreto) {
		nombre = param_nombre;
		tipo = param_tipo;
		valor = param_valor;
		precio = param_precio;
		cantidad = param_cantidad;
		secreto = param_secreto;
	}

	// Metodos getter para obtener informacion del item.
	std::string obtenerNombre() {
		return nombre;
	}

	std::string obtenerTipo() {
		return tipo;
	}

	int obtenerValor() {
		return valor;
	}

	int obtenerPrecio() {
		return precio;
	}

	int obtenerCantidad() {
		return cantidad;
	}

	bool esSecreto() {
		return secreto;
	}

	// Suma cantidad al item, por ejemplo al comprar repetido.
	void sumarCantidad(int cantidadSumada) {
		cantidad += cantidadSumada;
	}

	// Resta cantidad al item, por ejemplo al usar una poushon.
	void restarCantidad(int cantidadRestada) {
		cantidad -= cantidadRestada;

		// Este if evita que la cantidad baje de cero.
		if (cantidad < 0) {
			cantidad = 0;
		}
	}
};

// Clase base para personajes del juego.
// Tanto el heroe como los enemigos heredan de aqui.
class Personaje {
protected:
	std::string nombre;
	int vida;
	int vidaMaxima;
	int danio;

public:
	// Constructor base del personaje.
	Personaje(std::string param_nombre, int param_vida, int param_danio) {
		nombre = param_nombre;
		vida = param_vida;
		vidaMaxima = param_vida;
		danio = param_danio;
	}

	// Resta vida cuando un personaje recibe daño.
	void recibirDanio(int param_danio) {
		vida -= param_danio;

		// Este if evita que la vida quede en negativo.
		if (vida < 0) {
			vida = 0;
		}
	}

	// Regresa true si el personaje sigue con vida.
	bool estaVivo() {
		return vida > 0;
	}

	// Getters de informacion del personaje.
	std::string obtenerNombre() {
		return nombre;
	}

	int obtenerVida() {
		return vida;
	}

	int obtenerVidaMaxima() {
		return vidaMaxima;
	}

	int obtenerDanio() {
		return danio;
	}

	// Cura completamente al personaje.
	void curarCompleto() {
		vida = vidaMaxima;
	}

	// Cura una cantidad especifica sin pasar de la vida maxima.
	void curarCantidad(int cantidadCurada) {
		vida += cantidadCurada;

		// Este if evita que la curacion pase del maximo de vida.
		if (vida > vidaMaxima) {
			vida = vidaMaxima;
		}
	}
};

// Clase del jugador principal.
// Hereda de Personaje y agrega nivel, experiencia, oro e inventario.
class Heroe : public Personaje {
	int nivel;
	int experiencia;
	int oro;

	bool buffCampamentoActivo;
	bool PIMPIActivo;

	bool PIMPI;
	bool PIMPIComido;
	bool PIMPIEquipado;
	bool PIMPIAlimentado;

	int bonoEspada;
	int bonoArmadura;

	std::string espadaEquipada;
	std::string armaduraEquipada;

	std::vector<Item> inventario;

public:
	// Constructor del heroe.
	Heroe(std::string param_nombre, int param_vida, int param_danio, int param_oro)
		: Personaje(param_nombre, param_vida, param_danio) {
		nivel = 1;
		experiencia = 0;
		oro = param_oro;
		buffCampamentoActivo = false;
		PIMPIActivo = false;
		PIMPI = true;
		PIMPIComido = false;
		PIMPIEquipado = false;
		PIMPIAlimentado = false;
		bonoEspada = 0;
		bonoArmadura = 0;
		espadaEquipada = "Ninguna";
		armaduraEquipada = "Ninguna";

		inventario.push_back(Item("PIMPI", "PIMPI", 0, 0, 1, false));
	}

	// Muestra el estado del heroe durante el combate.
	void mostrarEstadoHeroe() {
		std::cout << "----- HEROE -----" << std::endl;
		std::cout << "Vida: " << vida << "/" << vidaMaxima << std::endl;
		std::cout << "Danio: " << danio << std::endl;
		std::cout << "Nivel: " << nivel << std::endl;
		std::cout << "Oro: " << oro << std::endl;
		std::cout << "Espada actual: " << espadaEquipada << std::endl;
		std::cout << "Armadura actual: " << armaduraEquipada << std::endl;
	}

	void mostrarEstadoCombate() {
		std::cout << "===== HEROE =====" << std::endl;
		std::cout << "Vida: " << vida << "/" << vidaMaxima << std::endl;
		std::cout << "Danio: " << danio << std::endl;
		std::cout << "Nivel: " << nivel << std::endl;
	}

	bool getPIMPI() {
		return PIMPI;
	}

	bool getPIMPIAlimentado() {
		return PIMPIAlimentado;
	}

	void usarPIMPIDesdeInventarioCombate() {
		usodePIMPI();
	}

	void comersePIMPIDesdeInventarioCombate() {
		comerPIMPI();
	}

	void comerPIMPI() {
		if (PIMPI) {
			curarCantidad(10);
			PIMPI = false;
			PIMPIComido = true;

			for (int i = 0; i < inventario.size(); i++) {
				if (inventario[i].obtenerNombre() == "PIMPI") {
					inventario.erase(inventario.begin() + i);
					break;
				}
			}

			std::cout << "Consumiste a PIMPI, recuperas 10 de vida." << std::endl;
			std::cout << "Te recuperaste un poco fisicamente pero te sientes deprimido." << std::endl;
		}
		else {
			std::cout << "Ya no esta PIMPI." << std::endl;
		}
	}

	void usodePIMPI() {
		if (PIMPI && !PIMPIActivo) {
			danio += 1;
			PIMPIActivo = true;
			PIMPIEquipado = true;
			std::cout << "Usaste a PIMPI. Tu danio aumento +1 durante este combate." << std::endl;
		}
		else if (!PIMPI) {
			std::cout << "Ya no esta PIMPI." << std::endl;
		}
		else {
			std::cout << "PIMPI ya esta siendo usado en este combate." << std::endl;
		}
	}

	void terminarUsoPIMPI() {
		if (PIMPIActivo) {
			danio -= 1;
			PIMPIActivo = false;
			PIMPI = false;

			for (int i = 0; i < inventario.size(); i++) {
				if (inventario[i].obtenerNombre() == "PIMPI") {
					inventario.erase(inventario.begin() + i);
					break;
				}
			}

			std::cout << std::endl;
			std::cout << "PIMPI lucho con gran valor durante el combate..." << std::endl;
			std::cout << "pero desafortunadamente sus heridas fueron graves." << std::endl;
			std::cout << "PIMPI murio por lesiones severas..." << std::endl;
		}
	}

	void usarObjetoSecretoDesdeInventario(int posicion) {
		usarObjetoSecreto(posicion);
	}

	void usarObjetoSecreto(int posicion) {
		if (!slotValidoInventario(posicion)) {
			return;
		}

		int opcion = 0;
		std::cout << "1. Usar en Heroe" << std::endl;
		std::cout << "2. Usar en PIMPI" << std::endl;

		opcion = pedirNumero("En quien deseas usarlo?");

		if (opcion == 1) {
			std::cout << "No paso nada..." << std::endl;
			inventario.erase(inventario.begin() + posicion);
		}
		else if (opcion == 2) {
			if (PIMPI) {
				PIMPIAlimentado = true;
				std::cout << "PIMPI consumio  ???" << std::endl;
				inventario.erase(inventario.begin() + posicion);
			}
			else {
				std::cout << "Ya no esta PIMPI." << std::endl;
			}
		}
		else {
			std::cout << "Opcion invalida." << std::endl;
		}
	}

	int obtenerBonoArmadura() {
		return bonoArmadura;
	}

	// Regresa la cantidad de oro actual del heroe.
	int obtenerOro() {
		return oro;
	}

	// Descuenta oro cuando se compra un objeto.
	void descontarOro(int cantidadOro) {
		oro -= cantidadOro;
	}

	// Suma experiencia al heroe.
	// Si llega a 100 o mas, sube de nivel y gana mas daño.
	void ganarExp(int expGanada) {
		experiencia += expGanada;
		std::cout << "Ganaste " << expGanada << " de experiencia." << std::endl;

		// Este if sirve para subir de nivel cuando se alcanza el limite de experiencia.
		if (experiencia >= 100) {
			experiencia = 0;
			nivel++;
			danio += 5;

			std::cout << "Subiste a nivel " << nivel << "." << std::endl;
			std::cout << "Tu danio aumento a " << danio << "." << std::endl;
		}
	}

	// Activa un buff temporal de daño desde la zona de descanso.
	void activarBuffCampamento() {
		// Este if evita que el buff se active dos veces seguidas.
		if (!buffCampamentoActivo) {
			danio += 2;
			buffCampamentoActivo = true;
			std::cout << "Te buffaste. Tu danio aumento temporalmente +2." << std::endl;
		}
		else {
			std::cout << "Ya tienes el buff activo." << std::endl;
		}
	}

	// Quita el buff temporal al finalizar el combate.
	void terminarBuffCampamento() {
		// Este if verifica si realmente habia un buff activo antes de quitarlo.
		if (buffCampamentoActivo) {
			danio -= 2;
			buffCampamentoActivo = false;
			std::cout << "El buff se acabo." << std::endl;
		}
	}

	// Agrega un item al inventario.
	// Si ya existe uno con el mismo nombre, solo aumenta su cantidad.
	void agregarItem(Item itemNuevo) {
		// Este for recorre todo el inventario para ver si el item ya existe.
		for (int i = 0; i < inventario.size(); i++) {
			// Este if compara el nombre del item actual con el que se intenta agregar.
			if (inventario[i].obtenerNombre() == itemNuevo.obtenerNombre()) {
				inventario[i].sumarCantidad(itemNuevo.obtenerCantidad());
				return;
			}
		}

		// Si no estaba repetido, se agrega como nuevo al inventario.
		inventario.push_back(itemNuevo);
	}

	// Muestra el inventario sin numeracion.
	void mostrarInventario() {
		std::cout << "----- INVENTARIO -----" << std::endl;

		// Este if muestra un mensaje especial si el inventario esta vacio.
		if (inventario.empty()) {
			std::cout << "No hay objetos en el inventario." << std::endl;
		}
		else {
			// Este for recorre todos los objetos para imprimirlos.
			for (int i = 0; i < inventario.size(); i++) {
				std::cout << "- " << inventario[i].obtenerNombre()
					<< " | Cantidad: " << inventario[i].obtenerCantidad() << std::endl;
			}
		}
	}

	// Muestra el inventario numerado para seleccionar un objeto.
	void mostrarInventarioNumerado() {
		std::cout << "----- INVENTARIO -----" << std::endl;

		// Este if muestra un mensaje especial si el inventario esta vacio.
		if (inventario.empty()) {
			std::cout << "No hay objetos en el inventario." << std::endl;
		}
		else {
			// Este for recorre todos los objetos para imprimirlos con numero.
			for (int i = 0; i < inventario.size(); i++) {
				std::cout << i + 1 << ". " << inventario[i].obtenerNombre()
					<< " | Cantidad: " << inventario[i].obtenerCantidad() << std::endl;
			}
		}
	}

	// Verifica si una posicion del inventario es valida.
	bool slotValidoInventario(int posicion) {
		return posicion >= 0 && posicion < inventario.size();
	}

	// Devuelve el nombre del item en cierta posicion del inventario.
	std::string obtenerNombreItemInventario(int posicion) {
		// Este if comprueba que la posicion exista antes de acceder al vector.
		if (slotValidoInventario(posicion)) {
			return inventario[posicion].obtenerNombre();
		}
		return "";
	}

	// Devuelve el tipo del item en cierta posicion del inventario.
	std::string obtenerTipoItemInventario(int posicion) {
		// Este if comprueba que la posicion exista antes de acceder al vector.
		if (slotValidoInventario(posicion)) {
			return inventario[posicion].obtenerTipo();
		}
		return "";
	}

	void mostrarInformacionObjeto(int posicion) {
		if (!slotValidoInventario(posicion)) {
			std::cout << "Opcion invalida." << std::endl;
			return;
		}

		std::string nombreItem = inventario[posicion].obtenerNombre();
		std::string tipoItem = inventario[posicion].obtenerTipo();
		int valorItem = inventario[posicion].obtenerValor();
		int precioItem = inventario[posicion].obtenerPrecio();
		int cantidadItem = inventario[posicion].obtenerCantidad();

		std::cout << "----- INFORMACION DEL OBJETO -----" << std::endl;
		std::cout << "Nombre: " << nombreItem << std::endl;
		std::cout << "Precio: " << precioItem << std::endl;
		std::cout << "Cantidad: " << cantidadItem << std::endl;

		if (nombreItem == "Poushon salud") {
			std::cout << "Descripcion: Cura al HEROE." << std::endl;
			std::cout << "Curacion exacta: +" << valorItem << " de vida." << std::endl;
		}
		else if (nombreItem == "Poushon fuerza") {
			std::cout << "Descripcion: Aumenta el danio del HEROE." << std::endl;
			std::cout << "Aumento exacto: +" << valorItem << " de danio." << std::endl;
		}
		else if (nombreItem == "Poushon fuego") {
			std::cout << "Descripcion: Poushon ofensiva de fuego." << std::endl;
			std::cout << "Danio estimado: " << valorItem << " al objetivo." << std::endl;
		}
		else if (nombreItem == "Poushon hielo") {
			std::cout << "Descripcion: Poushon ofensiva de hielo." << std::endl;
			std::cout << "Danio estimado: " << valorItem << " al objetivo." << std::endl;
		}
		else if (nombreItem == "Poushon veneno") {
			std::cout << "Descripcion: Poushon ofensiva de veneno." << std::endl;
			std::cout << "Danio estimado: " << valorItem << " al objetivo." << std::endl;
		}
		else if (nombreItem == "Poushon mana") {
			std::cout << "Descripcion: Poushon misteriosa." << std::endl;
			std::cout << "Valor interno: " << valorItem << "." << std::endl;
		}
		else if (tipoItem == "espada") {
			std::cout << "Descripcion: Arma que aumenta el ataque del HEROE." << std::endl;
			std::cout << "Bono exacto: +" << valorItem << " de danio." << std::endl;
		}
		else if (tipoItem == "armadura") {
			std::cout << "Descripcion: Equipo defensivo." << std::endl;
			std::cout << "Bono exacto: +" << valorItem << " de defensa/proteccion." << std::endl;
		}
		else {
			std::cout << "Descripcion: Objeto sin informacion registrada." << std::endl;
		}
	}

	// Elimina un item si su cantidad ya llego a cero.
	void eliminarItemSiCantidadCero(int posicion) {
		// Este if valida primero que la posicion exista.
		if (slotValidoInventario(posicion)) {
			// Este if revisa si la cantidad ya es cero o menor.
			if (inventario[posicion].obtenerCantidad() <= 0) {
				inventario.erase(inventario.begin() + posicion);
			}
		}
	}

	// Usa una poushon fuera de combate.
	void usarPoushonFueraDeCombate(int posicion) {
		// Este if evita acceder a una posicion invalida del inventario.
		if (!slotValidoInventario(posicion)) {
			std::cout << "Opcion invalida." << std::endl;
			return;
		}

		// Este if verifica que el objeto elegido sea del tipo poushon.
		if (inventario[posicion].obtenerTipo() == "poushon") {
			// Este if identifica especificamente la poushon de salud.
			if (inventario[posicion].obtenerNombre() == "Poushon salud") {
				curarCantidad(inventario[posicion].obtenerValor());
				std::cout << "Usaste Poushon salud. Recuperaste " << inventario[posicion].obtenerValor() << " de vida." << std::endl;
			}
			// Este else if identifica la poushon de fuerza.
			else if (inventario[posicion].obtenerNombre() == "Poushon fuerza") {
				danio += inventario[posicion].obtenerValor();
				std::cout << "Usaste Poushon fuerza. Tu danio aumento +" << inventario[posicion].obtenerValor() << "." << std::endl;
			}
			// Este else cubre el resto de poushons.
			else {
				std::cout << "Usaste " << inventario[posicion].obtenerNombre() << "." << std::endl;
			}

			// Se consume una unidad del item usado.
			inventario[posicion].restarCantidad(1);

			// Si se acabaron, se elimina del inventario.
			eliminarItemSiCantidadCero(posicion);
		}
		else {
			std::cout << "Ese objeto no se usa asi fuera de combate." << std::endl;
		}
	}

	// Usa una poushon durante el combate.
	void usarPoushonEnCombate(int posicion) {
		// Este if evita acceder a una posicion invalida del inventario.
		if (!slotValidoInventario(posicion)) {
			std::cout << "Opcion invalida." << std::endl;
			return;
		}

		// Este if verifica que el objeto sea una poushon.
		if (inventario[posicion].obtenerTipo() == "poushon") {
			// Este if aplica curacion si es poushon de salud.
			if (inventario[posicion].obtenerNombre() == "Poushon salud") {
				curarCantidad(inventario[posicion].obtenerValor());
				std::cout << "Usaste Poushon salud. Recuperaste " << inventario[posicion].obtenerValor() << " de vida." << std::endl;
			}
			// Este else if aplica buff de daño si es poushon de fuerza.
			else if (inventario[posicion].obtenerNombre() == "Poushon fuerza") {
				danio += inventario[posicion].obtenerValor();
				std::cout << "Usaste Poushon fuerza. Tu danio aumento +" << inventario[posicion].obtenerValor() << " en este combate." << std::endl;
			}
			// Este else cubre las otras poushons.
			else {
				std::cout << "Usaste " << inventario[posicion].obtenerNombre() << "." << std::endl;
			}

			// Se consume una unidad de la poushon usada.
			inventario[posicion].restarCantidad(1);

			// Si ya no quedan unidades, se elimina del inventario.
			eliminarItemSiCantidadCero(posicion);
		}
		else {
			std::cout << "Ese objeto no se usa asi en combate." << std::endl;
		}
	}

	// Equipa un objeto del inventario.
	void equiparObjeto(int posicion) {
		// Este if valida que la posicion exista.
		if (!slotValidoInventario(posicion)) {
			std::cout << "Opcion invalida." << std::endl;
			return;
		}

		std::string nombreItem = inventario[posicion].obtenerNombre();
		std::string tipoItem = inventario[posicion].obtenerTipo();
		int valorItem = inventario[posicion].obtenerValor();

		if (tipoItem == "espada") {
			// Si ya habia una espada equipada, regresa al inventario
			if (espadaEquipada != "Ninguna") {
				agregarItem(Item(espadaEquipada, "espada", bonoEspada, 0, 1, false));
				danio -= bonoEspada;
			}

			bonoEspada = valorItem;
			danio += bonoEspada;
			espadaEquipada = nombreItem;

			inventario.erase(inventario.begin() + posicion);

			std::cout << "Equipaste " << espadaEquipada << "." << std::endl;
		}
		else if (tipoItem == "armadura") {
			// Si ya habia una armadura equipada, regresa al inventario
			if (armaduraEquipada != "Ninguna") {
				agregarItem(Item(armaduraEquipada, "armadura", bonoArmadura, 0, 1, false));
			}

			bonoArmadura = valorItem;
			armaduraEquipada = nombreItem;

			inventario.erase(inventario.begin() + posicion);

			std::cout << "Equipaste " << armaduraEquipada << "." << std::endl;
		}
		else {
			std::cout << "Ese objeto no se puede equipar." << std::endl;
		}
	}

	// Descarta un objeto del inventario.
	void descartarObjeto(int posicion) {
		// Este if valida que la posicion exista.
		if (!slotValidoInventario(posicion)) {
			std::cout << "Opcion invalida." << std::endl;
			return;
		}

		if (inventario[posicion].obtenerNombre() == "PIMPI") {
			PIMPI = false;

			std::cout << "Elegiste descartar a PIMPI de la aventura ya que te parecio inutil" << std::endl;
			std::cout << "PIMPI triste se aleja de su antiguo amigo entre lagrimas....." << std::endl;

			inventario.erase(inventario.begin() + posicion);
			return;
		}

		std::cout << "Descartaste " << inventario[posicion].obtenerNombre() << "." << std::endl;
		inventario.erase(inventario.begin() + posicion);
	}
};

// Clase del enemigo.
// Tambien hereda de Personaje y añade la experiencia que entrega al ser derrotado.
class Enemigo : public Personaje {
	int expQueDa;

public:
	Enemigo(std::string param_nombre, int param_vida, int param_danio, int param_expQueDa)
		: Personaje(param_nombre, param_vida, param_danio) {
		expQueDa = param_expQueDa;
	}

	// Regresa la experiencia que otorga el enemigo.
	int obtenerExpQueDa() {
		return expQueDa;
	}
};

// Clase de la tienda.
// En este avance se enfoca en vender poushons. (Por ahora)
class Tienda {
	std::vector<Item> poushons;
	std::vector<Item> equipo;

public:
	// Constructor de la tienda.
	// Aqui se crean las poushons disponibles.
	Tienda() {
		equipo.push_back(Item("Espada oxidada", "espada", 3, 40, 1, false));
		equipo.push_back(Item("Espada de acero", "espada", 6, 80, 1, false));
		equipo.push_back(Item("Espada legendaria", "espada", 10, 120, 1, false));

		equipo.push_back(Item("Armadura rota", "armadura", 1, 30, 1, false));
		equipo.push_back(Item("Armadura de hierro", "armadura", 2, 60, 1, false));
		equipo.push_back(Item("Armadura divina", "armadura", 3, 100, 1, false));

		poushons.push_back(Item("Poushon salud", "poushon", 20, 20, 3, false));
		poushons.push_back(Item("Poushon mana", "poushon", 10, 15, 3, false));
		poushons.push_back(Item("Poushon fuerza", "poushon", 2, 25, 2, false));
		poushons.push_back(Item("Poushon veneno", "poushon", 5, 15, 2, false));
		poushons.push_back(Item("Poushon hielo", "poushon", 5, 15, 2, false));
		poushons.push_back(Item("Poushon fuego", "poushon", 5, 15, 2, false));
		poushons.push_back(Item("¿¿¿¿¿?????", "especial", 0, 10, 1, true));
	}

	void mostrarEquipo() {
		std::cout << "----- EQUIPO -----" << std::endl;

		for (int i = 0; i < 6; i++) {
			if (equipo[i].obtenerCantidad() > 0) {
				std::cout << "Stock " << i + 1 << " - " << equipo[i].obtenerNombre()
					<< " | Precio: " << equipo[i].obtenerPrecio() << std::endl;
			}
			else {
				std::cout << "STOCK " << i + 1 << " - VACIO" << std::endl;
			}
		}
	}

	// Muestra el estante visual de poushons.
	void mostrarPoushons() {
		int anchoBloque = 22;

		std::cout << "----------------------------  ESTANTE  ----------------------------" << std::endl;
		std::cout << std::endl;

		// Este for externo divide el estante en dos filas de 3 objetos.
		for (int i = 0; i < 6; i += 3) {

			// Estos for internos imprimen cada parte del dibujo ASCII de cada poushon.
			for (int j = i; j < i + 3 && j < 6; j++) {
				if (poushons[j].obtenerCantidad() > 0) {
					std::cout << centrarTexto("_____", anchoBloque);
				}
				else {
					std::cout << centrarTexto("", anchoBloque);
				}

				if (j < i + 2) {
					std::cout << "|";
				}
			}

			if (i == 0 && poushons[6].obtenerCantidad() > 0) {
				std::cout << centrarTexto("                                                   7", 20);
			}

			std::cout << std::endl;

			for (int j = i; j < i + 3 && j < 6; j++) {
				if (poushons[j].obtenerCantidad() > 0) {
					std::cout << centrarTexto("\\___/", anchoBloque);
				}
				else {
					std::cout << centrarTexto("", anchoBloque);
				}

				if (j < i + 2) {
					std::cout << "|";
				}
			}

			if (i == 0 && poushons[6].obtenerCantidad() > 0) {
				std::cout << centrarTexto("", 20);
			}

			std::cout << std::endl;

			for (int j = i; j < i + 3 && j < 6; j++) {
				if (poushons[j].obtenerCantidad() > 0) {
					std::cout << centrarTexto("|   |", anchoBloque);
				}
				else {
					std::cout << centrarTexto("", anchoBloque);
				}

				if (j < i + 2) {
					std::cout << "|";
				}
			}

			if (i == 0 && poushons[6].obtenerCantidad() > 0) {
				std::cout << centrarTexto("", 20);
			}

			std::cout << std::endl;

			for (int j = i; j < i + 3 && j < 6; j++) {
				if (poushons[j].obtenerCantidad() > 0) {
					std::cout << centrarTexto("/       \\", anchoBloque);
				}
				else {
					std::cout << centrarTexto("", anchoBloque);
				}

				if (j < i + 2) {
					std::cout << "|";
				}
			}

			if (i == 0 && poushons[6].obtenerCantidad() > 0) {
				std::cout << centrarTexto("", 20);
			}

			std::cout << std::endl;

			for (int j = i; j < i + 3 && j < 6; j++) {
				if (poushons[j].obtenerCantidad() > 0) {
					std::string lineaNumero = "|    " + std::to_string(j + 1) + "    |";
					std::cout << centrarTexto(lineaNumero, anchoBloque);
				}
				else {
					std::cout << centrarTexto("", anchoBloque);
				}

				if (j < i + 2) {
					std::cout << "|";
				}
			}

			if (i == 0 && poushons[6].obtenerCantidad() > 0) {
				std::cout << centrarTexto("", 20);
			}

			std::cout << std::endl;

			for (int j = i; j < i + 3 && j < 6; j++) {
				if (poushons[j].obtenerCantidad() > 0) {
					std::cout << centrarTexto("\\_______/", anchoBloque);
				}
				else {
					std::cout << centrarTexto("", anchoBloque);
				}

				if (j < i + 2) {
					std::cout << "|";
				}
			}

			if (i == 0 && poushons[6].obtenerCantidad() > 0) {
				std::cout << centrarTexto("", 20);
			}

			std::cout << std::endl;

			for (int j = i; j < i + 3 && j < 6; j++) {
				if (poushons[j].obtenerCantidad() > 0) {
					std::cout << centrarTexto(poushons[j].obtenerNombre(), anchoBloque);
				}
				else {
					std::cout << centrarTexto("STOCK " + std::to_string(j + 1) + " - VACIO", anchoBloque);
				}

				if (j < i + 2) {
					std::cout << "|";
				}
			}

			if (i == 0 && poushons[6].obtenerCantidad() > 0) {
				std::cout << centrarTexto("", 20);
			}

			std::cout << std::endl << std::endl;
		}
	}

	// Permite comprar una poushon si hay stock y oro suficiente.
	void comprarEquipo(Heroe& heroe) {
		mostrarEquipo();
		int opcion = pedirNumero("Que equipo deseas comprar?");

		if (opcion >= 1 && opcion <= 6) {
			if (equipo[opcion - 1].obtenerCantidad() > 0) {
				if (heroe.obtenerOro() >= equipo[opcion - 1].obtenerPrecio()) {
					heroe.descontarOro(equipo[opcion - 1].obtenerPrecio());

					heroe.agregarItem(Item(
						equipo[opcion - 1].obtenerNombre(),
						equipo[opcion - 1].obtenerTipo(),
						equipo[opcion - 1].obtenerValor(),
						equipo[opcion - 1].obtenerPrecio(),
						1,
						false
					));

					equipo[opcion - 1].restarCantidad(1);

					std::cout << "Gracias por su compra." << std::endl;
					std::cout << "Oro restante: " << heroe.obtenerOro() << std::endl;
				}
				else {
					std::cout << "No tienes oro suficiente." << std::endl;
				}
			}
			else {
				std::cout << "Ese stock esta vacio." << std::endl;
			}
		}
		else {
			std::cout << "Opcion invalida." << std::endl;
		}
	}

	// Permite comprar una poushon si hay stock y oro suficiente.
	void comprarPoushon(Heroe& heroe) {
		mostrarPoushons();
		int opcion = pedirNumero("Que Poushon deseas comprar?");

		if (opcion >= 1 && opcion <= 7) {
			if (poushons[opcion - 1].obtenerCantidad() > 0) {
				if (opcion == 7) {
					std::cout << "Poushon seleccionada: ???" << std::endl;
					std::cout << "Descripcion: ±N@ΩIñ|F°¿L¹¯E" << std::endl;
					std::cout << "Precio: 10" << std::endl;
					std::cout << "Stock disponible: 1" << std::endl;
				}
				else {
					std::cout << "Poushon seleccionada: " << poushons[opcion - 1].obtenerNombre() << std::endl;
					std::cout << "Precio: " << poushons[opcion - 1].obtenerPrecio() << std::endl;
					std::cout << "Stock disponible: " << poushons[opcion - 1].obtenerCantidad() << std::endl;
				}
				int confirmar = pedirNumero("1. Comprar\n2. Salir");

				if (confirmar == 1) {
					int cantidadCompra = pedirNumero("Cuantas deseas comprar?");

					if (cantidadCompra <= 0) {
						std::cout << "Cantidad invalida." << std::endl;
					}
					else if (cantidadCompra > poushons[opcion - 1].obtenerCantidad()) {
						std::cout << "No hay suficiente stock." << std::endl;
					}
					else {
						int costoTotal = poushons[opcion - 1].obtenerPrecio() * cantidadCompra;

						if (heroe.obtenerOro() >= costoTotal) {
							heroe.descontarOro(costoTotal);

							heroe.agregarItem(Item(
								poushons[opcion - 1].obtenerNombre(),
								poushons[opcion - 1].obtenerTipo(),
								poushons[opcion - 1].obtenerValor(),
								poushons[opcion - 1].obtenerPrecio(),
								cantidadCompra,
								poushons[opcion - 1].esSecreto()
							));

							poushons[opcion - 1].restarCantidad(cantidadCompra);

							std::cout << "Gracias por su compra." << std::endl;
							std::cout << "Compraste " << cantidadCompra << " unidad(es)." << std::endl;
							std::cout << "Oro restante: " << heroe.obtenerOro() << std::endl;
						}
						else {
							std::cout << "No tienes oro suficiente." << std::endl;
						}
					}
				}
			}
			else {
				std::cout << "Ese stock esta vacio." << std::endl;
			}
		}
		else {
			std::cout << "Opcion invalida." << std::endl;
		}
	}
};

// Clase principal que organiza el flujo interno del sistema.
// Aqui se concentra la logica de combate, inventario, tienda y descanso.
class Juego {
	Heroe& heroe;
	Tienda tienda;

	Enemigo& general1;
	Enemigo& general2;
	Enemigo& general3;
	Enemigo& reyDemonio;

public:
	Juego(Heroe& _heroe, Enemigo& _general1, Enemigo& _general2, Enemigo& _general3, Enemigo& _reyDemonio)
		: heroe(_heroe), general1(_general1), general2(_general2), general3(_general3), reyDemonio(_reyDemonio) {
	}

	// Inventario que se puede abrir durante un combate.
	void inventarioCombate() {
		int opcion = 0;

		// Este while mantiene abierto el inventario hasta que el jugador decida salir.
		while (opcion != 3) {
			std::cout << std::endl;
			heroe.mostrarInventario();
			std::cout << std::endl;
			std::cout << "1. Seleccionar objeto" << std::endl;
			std::cout << "2. Informacion de object" << std::endl;
			std::cout << "3. Salir del inventario" << std::endl;

			opcion = pedirNumero("Que deseas hacer?");
			std::cout << std::endl;

			// Este if permite seleccionar un objeto del inventario.
			if (opcion == 1) {
				std::cout << std::endl;
				heroe.mostrarInventarioNumerado();

				int slot = pedirNumero("Que objeto deseas seleccionar?");
				slot--;

				std::cout << std::endl;

				// Este if valida que el slot exista.
				if (!heroe.slotValidoInventario(slot)) {
					std::cout << "Opcion invalida." << std::endl;
				}
				else {
					std::string nombreItem = heroe.obtenerNombreItemInventario(slot);
					std::string tipoItem = heroe.obtenerTipoItemInventario(slot);

					if (nombreItem == "PIMPI") {
						int opcionPIMPI = 0;
						std::cout << "1. Usar" << std::endl;
						std::cout << "2. Consumir" << std::endl;
						std::cout << "3. Salir" << std::endl;

						opcionPIMPI = pedirNumero("Que deseas hacer con PIMPI?");
						std::cout << std::endl;

						if (opcionPIMPI == 1) {
							heroe.usarPIMPIDesdeInventarioCombate();
							break;
						}
						else if (opcionPIMPI == 2) {
							heroe.comersePIMPIDesdeInventarioCombate();
							break;
						}
						else if (opcionPIMPI == 3) {
							std::cout << "Saliendo." << std::endl;
						}
						else {
							std::cout << "Opcion invalida." << std::endl;
						}
					}
					else if (tipoItem == "poushon") {
						heroe.usarPoushonEnCombate(slot);
						break;
					}
					// Este else if impide usar equipo como si fuera consumible.
					else if (tipoItem == "espada" || tipoItem == "armadura") {
						std::cout << "Ese equipo no se usa en medio del combate." << std::endl;
					}
					else {
						std::cout << "Ese objeto no se puede usar en combate." << std::endl;
					}
				}
			}
			else if (opcion == 2) {
				std::cout << std::endl;
				heroe.mostrarInventarioNumerado();

				int slot = pedirNumero("De que objeto quieres ver la informacion?");
				slot--;

				std::cout << std::endl;
				heroe.mostrarInformacionObjeto(slot);
			}
			else if (opcion == 3) {
				std::cout << "Saliendo del inventario." << std::endl;
			}
			else {
				std::cout << "Opcion invalida." << std::endl;
			}
		}
	}

	// Inventario que se usa en la zona de descanso.
	void inventarioDescanso() {
		int opcion = 0;

		// Este while mantiene abierto el inventario hasta que el jugador decida salir.
		while (opcion != 5) {
			std::cout << std::endl;
			heroe.mostrarInventario();
			std::cout << std::endl;
			std::cout << "1. Usar objeto" << std::endl;
			std::cout << "2. Equipar objeto" << std::endl;
			std::cout << "3. Informacion de objeto" << std::endl;
			std::cout << "4. Descartar objeto" << std::endl;
			std::cout << "5. Salir del inventario" << std::endl;

			opcion = pedirNumero("Que desea hacer?");
			std::cout << std::endl;

			// Este if permite usar un objeto.
			if (opcion == 1) {
				std::cout << std::endl;
				heroe.mostrarInventarioNumerado();

				int slot = pedirNumero("Que objeto deseas usar?");
				slot--;

				std::cout << std::endl;

				// Este if valida que el slot exista.
				if (!heroe.slotValidoInventario(slot)) {
					std::cout << "Opcion invalida." << std::endl;
				}
				else {
					std::string nombreItem = heroe.obtenerNombreItemInventario(slot);
					std::string tipoItem = heroe.obtenerTipoItemInventario(slot);

					if (nombreItem == "PIMPI") {
						int opcionPIMPI = 0;
						std::cout << "1. Consumir" << std::endl;
						std::cout << "2. Salir" << std::endl;

						opcionPIMPI = pedirNumero("Que deseas hacer con PIMPI?");
						std::cout << std::endl;

						if (opcionPIMPI == 1) {
							heroe.comerPIMPI();
						}
						else if (opcionPIMPI == 2) {
							std::cout << "Saliendo." << std::endl;
						}
						else {
							std::cout << "Opcion invalida." << std::endl;
						}
					}
					else if (tipoItem == "poushon") {
						heroe.usarPoushonFueraDeCombate(slot);
					}
					else if (tipoItem == "especial") {
						heroe.usarObjetoSecretoDesdeInventario(slot);
					}
					else {
						std::cout << "Ese objeto no se usa asi." << std::endl;
					}
				}
			}
			// Este else if permite equipar un objeto.
			else if (opcion == 2) {
				std::cout << std::endl;
				heroe.mostrarInventarioNumerado();

				int slot = pedirNumero("Que objeto deseas equipar?");
				slot--;

				std::cout << std::endl;

				// Este if valida que el slot exista.
				if (!heroe.slotValidoInventario(slot)) {
					std::cout << "Opcion invalida." << std::endl;
				}
				else {
					heroe.equiparObjeto(slot);
				}
			}
			else if (opcion == 3) {
				std::cout << std::endl;
				heroe.mostrarInventarioNumerado();

				int slot = pedirNumero("De que objeto quieres ver la informacion?");
				slot--;

				std::cout << std::endl;
				heroe.mostrarInformacionObjeto(slot);
			}
			// Este else if permite descartar un objeto.
			else if (opcion == 4) {
				std::cout << std::endl;
				heroe.mostrarInventarioNumerado();

				int slot = pedirNumero("Que objeto deseas descartar?");
				slot--;

				std::cout << std::endl;
				heroe.descartarObjeto(slot);
			}
			else if (opcion == 5) {
				std::cout << "Saliendo del inventario." << std::endl;
			}
			else {
				std::cout << "Opcion invalida." << std::endl;
			}
		}
	}

	// Menu de la tienda.
	void menuTienda() {
		int opcion = 0;

		while (opcion != 3) {
			std::cout << std::endl;
			std::cout << "----- TIENDA -----" << std::endl;
			std::cout << "1. Equipo" << std::endl;
			std::cout << "2. Poushons" << std::endl;
			std::cout << "3. Salir de la tienda" << std::endl;

			opcion = pedirNumero("Seleccione una opcion:");

			if (opcion == 1) {
				tienda.comprarEquipo(heroe);
			}
			else if (opcion == 2) {
				tienda.comprarPoushon(heroe);
			}
			else if (opcion == 3) {
				std::cout << "Saliendo de la tienda." << std::endl;
			}
			else {
				std::cout << "Opcion invalida." << std::endl;
			}
		}
	}

	// Sistema principal de combate.
	// Regresa true si el heroe gana y false si pierde.
	bool combate(Enemigo& enemigo) {
		std::cout << std::endl;
		std::cout << "----- COMBATE CONTRA " << enemigo.obtenerNombre() << " -----" << std::endl;

		// Este while mantiene el combate activo mientras ambos sigan con vida.
		while (heroe.estaVivo() && enemigo.estaVivo()) {
			std::cout << std::endl;
			heroe.mostrarEstadoCombate();
			std::cout << "\nEnemigo: " << enemigo.obtenerNombre() << std::endl;
			std::cout << "Vida enemigo: " << enemigo.obtenerVida() << "/" << enemigo.obtenerVidaMaxima() << std::endl;
			std::cout << "Danio enemigo: " << enemigo.obtenerDanio() << std::endl;
			std::cout << std::endl;

			std::cout << "1. Atacar" << std::endl;
			std::cout << "2. Inventario" << std::endl;

			int opcionTurno = pedirNumero("Que desea hacer?");

			// Este if corresponde al ataque basico del heroe.
			if (opcionTurno == 1) {
				std::cout << "\nEl HEROE ataca y hace " << heroe.obtenerDanio() << " de danio." << std::endl;
				enemigo.recibirDanio(heroe.obtenerDanio());
				std::cout << "Vida restante de " << enemigo.obtenerNombre() << ": " << enemigo.obtenerVida() << std::endl;
			}
			// Este else if permite abrir el inventario en medio del combate.
			else if (opcionTurno == 2) {
				inventarioCombate();
			}
			else {
				std::cout << "Opcion invalida. Pierdes el turno." << std::endl;
			}

			// Este if revisa si el enemigo murio despues del turno del heroe.
			if (!enemigo.estaVivo()) {
				system("cls");
				std::cout << "Derrotaste a " << enemigo.obtenerNombre() << "." << std::endl;

				// Este if da experiencia solo si el enemigo esta configurado para darla.
				if (enemigo.obtenerExpQueDa() > 0) {
					heroe.ganarExp(enemigo.obtenerExpQueDa());
				}

				heroe.terminarBuffCampamento();
				heroe.terminarUsoPIMPI();
				return true;
			}

			// Si el enemigo sigue vivo, entonces le toca atacar.
			int danioEnemigo = enemigo.obtenerDanio();
			int defensaHeroe = heroe.obtenerBonoArmadura();
			int danioReal = danioEnemigo - defensaHeroe;

			if (danioReal < 0) {
				danioReal = 0;
			}

			std::cout << enemigo.obtenerNombre() << " ataca y hace " << danioEnemigo << " de danio." << std::endl;

			if (defensaHeroe > 0) {
				std::cout << "Tu armadura reduce " << defensaHeroe << " de danio." << std::endl;
			}

			std::cout << "Danio recibido: " << danioReal << std::endl;
			heroe.recibirDanio(danioReal);
			std::cout << "Vida restante del HEROE: " << heroe.obtenerVida() << std::endl;

			// Este if revisa si el heroe murio despues del turno del enemigo.
			if (!heroe.estaVivo()) {
				system("cls");
				std::cout << "El HEROE ha sido derrotado." << std::endl;
				return false;
			}
		}

		return false;
	}

	// Zona entre combates donde el jugador puede prepararse.
	void zonaDescanso() {
		PlaySound(TEXT("Campamento.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		int opcion = 0;

		// Este while mantiene al jugador en la zona de descanso
		// hasta que elija continuar.
		while (opcion != 6) {
			std::cout << std::endl;
			std::cout << "----- ZONA DE DESCANSO -----" << std::endl;
			std::cout << "1. Tienda" << std::endl;
			std::cout << "2. Estado de Heroe" << std::endl;
			std::cout << "3. Inventario" << std::endl;
			std::cout << "4. Descansar" << std::endl;
			std::cout << "5. Buffarse" << std::endl;
			std::cout << "6. Continuar" << std::endl;

			opcion = pedirNumero("Seleccione una opcion:");

			// Este if abre la tienda.
			if (opcion == 1) {
				menuTienda();
			}
			if (opcion == 2) {
				heroe.mostrarEstadoHeroe();
			}
			// Este else if abre el inventario de descanso.
			else if (opcion == 3) {
				inventarioDescanso();
			}
			// Este else if cura completamente al heroe.
			else if (opcion == 4) {
				heroe.curarCompleto();
				std::cout << "Descansaste y recuperaste toda tu vida." << std::endl;
			}
			// Este else if activa el buff temporal de daño.
			else if (opcion == 5) {
				heroe.activarBuffCampamento();
			}
			else if (opcion == 6) {
				std::cout << "\nContinuando la aventura..." << std::endl;
			}
			else {
				std::cout << "Opcion invalida." << std::endl;
			}
		}
		PlaySound(NULL, 0, 0);
	}

	// Muestra el final dependiendo del resultado del juego.
	void verificarFinal() {
		// Este if se activa si el heroe murio.
		if (!heroe.estaVivo()) {
			std::cout << "\n----- FINAL MALO -----" << std::endl;
			std::cout << "El HEROE murio y el reino fue destruido." << std::endl;
		}
		else if (heroe.getPIMPIAlimentado() && heroe.getPIMPI()) {
			PlaySound(NULL, 0, 0);
			PlaySound(TEXT("Who Will Know.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

			std::cout << "\n----- FINAL OCULTO -----" << std::endl;
			std::cout << "PIMPI se ............................." << std::endl;
			std::cout << "y termina con ............................." << std::endl;
		}
		else {
			PlaySound(NULL, 0, 0);
			PlaySound(TEXT("Stars At Our Backs.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

			std::cout << "\n----- FINAL BUENO -----" << std::endl;
			std::cout << "Derrotaste al Rey Demonio y salvaste el reino." << std::endl;
		}
	}
};

// Esta funcion imprime texto lentamente.
// Si el usuario presiona una tecla, el texto se muestra completo de golpe.
void TextoOmitible(std::string texto, int velocidad)
{
	// Este for recorre letra por letra el texto recibido.
	for (int i = 0; i < texto.size(); i++)
	{
		// Este if permite omitir la animacion de escritura si se presiona una tecla.
		if (_kbhit())
		{
			_getch();
			std::cout << texto.substr(i);
			std::cout.flush();
			return;
		}

		std::cout << texto[i];
		std::cout.flush();
		Sleep(velocidad);
	}
}

// Esta funcion pausa el programa hasta que el usuario presione una tecla.
void PresionaParaContinuar()
{
	std::cout << "\n\nPresiona una tecla para continuar...";
	_getch();
} 

int main()
{
	// Se crea el heroe principal con vida, daño y oro inicial.
	Heroe heroe("HEROE", 100, 100, 500);

	// Se crean los enemigos principales del juego con su vida, daño y experiencia otorgada.
	Enemigo general1("General 1", 100, 10, 100);
	Enemigo general2("General 2", 200, 15, 100);
	Enemigo general3("General 3", 300, 20, 100);
	Enemigo reyDemonio("REY DEMONIO", 500, 30, 0);

	// Se crea el objeto Juego, que conecta al heroe con enemigos y sistemas del juego.
	Juego juego(heroe, general1, general2, general3, reyDemonio);

	// Comienza la musica inicial del juego.
	PlaySound(TEXT("The Legend.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	// Historia inicial del juego.
	std::string Prologo =
		"Hace mucho mucho tiempo, habia un reino pacifico en los confines de la tierra, que vivia feliz y en armonia"
		"\npero un dia el cielo se oscurecio y la tierra se abrio, dejando salir a criaturas espelusnantes y aterradoras"
		"\nde las grietas que comenzaron a destruir y masacrar el reino, iniciando una era de guerra contra estas criaturas"
		"\ndenominadas \"demonios\" las cuales eran dirigidas por su rey, \"EL REY DEMONIO\" junto con sus tres generales"
		"\nlos cuales eran demonios de alto poder y enbergadura capaces de destruir ciudades enteras por si solos"
		"\n\nel rey humano ante tal situacion hizo todo lo posible para defender a su reino, mando a su ejercito"
		"\ny mando a llamar a incontables heroes para que derrotaran a los cuatro generales y al REY DEMONIO;"
		"\nuchos ya han muerto intentando poner fin a esta guerra pero ninguno lo a logrado"
		"\npero un dia un autoproclamado HEROE se presenta frente al palacio diciendo que el junto a su compañero: PIMPI"
		"\nseran los que pondran fin a esta guerra y traeran nuevamente una era de paz"
		"\n\nel rey ante tal discurso se queda conmovido y le da al heroe \"500\" de oro para que pueda emprender su viaje"
		"\nasi el HEROE junto con su compañero iniciaron su viaje en direccion al castillo del primer general\n\n";

	TextoOmitible(Prologo, 75);
	PresionaParaContinuar();

	PlaySound(NULL, 0, 0);

	system("cls");

	PlaySound(TEXT(""), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	std::string textoIntermedio1 =
		"\nLos primeros dias de viaje estuvieron marcados por caminos destruidos, humo en el horizonte y los restos de aldeas"
		"\nque habian caido ante el ejercito demoniaco. mientras mas se acercaban al territorio del primer general, mas frecuentes"
		"\ny violentos se volvian los enfrentamientos. escuadrones de demonios, bestias salvajes y guardianes armados"
		"\nsalian a su paso una y otra vez, obligando al HEROE a pelear sin descanso"

		"\n\nal principio cada combate parecia una lucha por sobrevivir, pero poco a poco algo comenzo a cambiar"
		"\ncon cada enemigo derrotado, con cada herida soportada y con cada obstaculo superado"
		"\nel HEROE sentia como si una nueva fuerza despertara dentro de su cuerpo"

		"\n\nera como si, al enfrentarse a enemigos mas poderosos, sus propios limites comenzaran a romperse"
		"\nsin comprenderlo del todo, el HEROE habia comenzado a alcanzar nuevos niveles de poder"

		"\n\nimpulsado por esa determinacion, el HEROE junto a PIMPI se abrio paso entre las tropas del enemigo"
		"\nderribo las defensas exteriores y finalmente cruzo las enormes puertas de la primera fortaleza"

		"\n\nel sonido de sus pasos resonaba en la sala principal cuando un silencio pesado cubrio el lugar..."

		"\n\nentonces, desde las sombras del salon, una gigantesca figura comenzo a acercarse lentamente.\n\n";

	TextoOmitible(textoIntermedio1, 35);
	PresionaParaContinuar();

	PlaySound(NULL, 0, 0);

	system("cls");

	PlaySound(TEXT(""), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	std::string presentacionGeneral1 =
		"\nuna risa grave y exagerada retumbo por toda la fortaleza"

		"\n\nla enorme figura salio de entre las sombras mostrando por fin su grotesca silueta : un demonio gigantesco"
		"\nancho como una muralla cubierto de lujosos adornos, y con una mirada cargada de burla y arrogancia"

		"\ncada una de sus pisadas hacia temblar el suelo, como si la propia fortaleza se inclinara ante su presencia"
		"\n\n- \"asi que tu eres la persona que tanto ruido ha hecho en mis dominios...\""
		"\n\nel monstruo dejo escapar otra carcajada, golpeandose el pecho con orgullo"                                            //|
		"\n\n- \"yo soy Venedictuz Decimuz... y esta fortaleza es la tumba donde vienen a morir los ilusos que creen poder desafiarme a mi y a nuestra raza.\""

		"\n\nsus pequenios ojos se posaron entonces sobre PIMPI, y su sonrisa se ensancho aun mas"

		"\n\n- \"hahahahaha... viniste hasta aqui con esa cosita a tu lado? debo admitirlo, tienes agallas... o simplemente eres"
		"\ndemasiado estupido para entender donde te metiste\""

		"\n\nVenedictuz dio un paso al frente, tronando su grueso cuello y levantando su enorme arma con total despreocupacion"

		"\n\n- \"Ven y acercate entonces supuesto HEROE, te convertire a ti en mi cena y a tu amiguito en mi postre.....\"\n\n";

	TextoOmitible(presentacionGeneral1, 55);
	PresionaParaContinuar();

	PlaySound(NULL, 0, 0);

	system("cls");

	// Comienza la musica del primer jefe.
	PlaySound(TEXT("Gang-Plank Galleon.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	// Primer combate.
	// Si pierde, se muestra derrota y termina el programa.
	if (!juego.combate(general1)) {
		PlaySound(NULL, 0, 0);
		PlaySound(TEXT("Derrota.wav"), NULL, SND_FILENAME | SND_ASYNC);
		juego.verificarFinal();
		_getch();
		return 0;
	}

	PlaySound(NULL, 0, 0);
	PlaySound(TEXT("Victoria del FINAL.wav"), NULL, SND_FILENAME | SND_ASYNC);

	std::cout << "\n\n---HISTORIA---" << std::endl;
	std::string mensajePostGeneral1 =
		"\nTras una dura batalla, Venedictuz Decimuz finalmente cayo ante el HEROE"

		"\n\nLa enorme fortaleza quedo en silencio, como si incluso las piedras hubieran sentido el peso de aquella derrota"
		"\nPor primera vez, una de las grandes murallas del Rey Demonio habia sido derribada"

		"\n\nSin embargo, en lugar de traer calma, aquella victoria solo dejo una certeza mas pesada en el aire..."
		"\nsi ese era apenas el primero de los generales, entonces el camino que quedaba por delante seria todavia mas cruel"

		"\n\nAun asi, el HEROE no dio un paso atras"
		"\nEl siguiente campamento lo aguardaba, y con el, la ruta hacia una nueva batalla\n";

	TextoOmitible(mensajePostGeneral1, 75);
	PresionaParaContinuar();
	system("cls");

	// Zona de descanso despues del primer combate.
	juego.zonaDescanso();

	system("cls");

	PlaySound(TEXT(""), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	// AUN POR MEJORAR
	std::string textoIntermedio2 =
		"Continuando la aventura...."
		"\nLa caida de Venedictuz Decimuz marco la primera gran victoria del HEROE, pero la guerra estaba lejos de terminar"

		"\n\ntras un breve descanso, el HEROE retomo el camino, esta vez se dirigio"
		"\na los territorios que estaban activamente en guerras"
		"\ny combates, dejando atras las ruinas ruinas donde estaba y en su lugar llendo hacia enormes campos de batalla"
		"\ncubiertos de armas rotas, armaduras partidas y restos de incontables enfrentamientos"

		"\n\nya no eran solo grupos de demonios sueltas las que salian a detenerlo"
		"\nahora eran destacamentos mejor organizados, tropas mas resistentes y"
		"\ndemonios capaces de coordinarse como verdaderos guerreros"

		"\n\nsin embargo, el HEROE ya no era el mismo que habia salido del reino"
		"\nAhora era mas rapido, mas fuerte y mas decidido, comenzo a abrirse paso entre las filas enemigas"
		"\ncon una ferocidad que incluso los demonios empezaron a temer"

		"\n\nal avanzar, una sensacion distinta comenzo a apoderarse del ambiente"
		"\nUna especie de sed de sangre y pelea,"
		"\nahora se respiraba la presencia de un guerrero"
		"\nuno que no solo esperaba al HEROE, sino que parecia ansioso por enfrentarlo"

		"\n\nal final del camino, una nueva fortaleza se alzaba frente a el"
		"\nrodeada por un campo de guerra silencioso con hedor de hierro y sangre"

		"\n\ny en medio de ese silencio, una voz profunda y firme resono desde el frente\n\n"; 

	TextoOmitible(textoIntermedio2, 75);
	PresionaParaContinuar();

	PlaySound(NULL, 0, 0);

	system("cls");

	PlaySound(TEXT(""), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	// AUN POR MEJORAR
	std::string presentacionGeneral2 =
		"De pie frente a la entrada de la fortaleza se encontraba un demonio de imponente estatura, con el"
		"\ncuerpo marcado por incontables batallas y una presencia que imponia respeto incluso antes de blandir su arma"

		"\n\nsu mirada era firme, pero lejos de mostrar desprecio, parecia reflejar autentico interes"

		"\n\n- \"Asi que tu eres quien ha derrotado a Venedictuz...\""

		"\n\nel demonio sonrio ligeramente, como si por fin algo hubiera despertado su atencion"

		"\n\n-\"Debo admitir que tenia curiosidad no cualquiera logra llegar hasta aqui abriendose paso entre nuestras filas\""

		"\n\napoyando su enorme arma sobre el suelo, el guerrero observo al HEROE de arriba abajo"
		"\ncomo si intentara medir su valor con solo mirarlo"

		"\n\n-\"Mi nombre es Karg' Aalh, sirvo con orgullo a su majestad, y todo aquel que interfiera en su camino debe ser derribado\""

		"\n\npor un instante guardo silencio, pero enseguida su sonrisa se ensancho, ahora con un brillo casi entusiasta"

		"\n\n- \"Sin embargo.... seria una mentira decir que no estoy complacido"
		"\nhace mucho que no aparece alguien capaz de llegar tan lejos\""

		"\n\nKarg' Aalh dio un paso al frente y ajusto su postura como un guerrero"
		"\npreparandose para una pelea largamente esperada"

		"\n\n- \"Vamos, HEROE muestrame si de verdad eres digno de todo este caos que has provocado"
		"\nespero que, al menos, seas una pelea memorable.....\"\n\n";

	TextoOmitible(presentacionGeneral2, 75);
	PresionaParaContinuar();

	PlaySound(NULL, 0, 0);

	system("cls");

	// Comienza la musica del segundo jefe.
	PlaySound(TEXT("Out of Tartarus.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	// Segundo combate.
	// Si pierde, se muestra derrota y termina el programa.
	if (!juego.combate(general2)) {
		PlaySound(NULL, 0, 0);
		PlaySound(TEXT("Derrota.wav"), NULL, SND_FILENAME | SND_ASYNC);
		juego.verificarFinal();
		_getch();
		return 0;
	}

	PlaySound(NULL, 0, 0);
	PlaySound(TEXT("Victoria del FINAL.wav"), NULL, SND_FILENAME | SND_ASYNC);

	std::cout << "\n\n---HISTORIA---" << std::endl;
	std::string mensajePostGeneral2 =
		"\nKarg' Aalh fue derrotado, y con su caida el estruendo de la batalla parecio extinguirse por un instante"

		"\n\nLo que antes parecia imposible comenzaba a volverse real"
		"\nel HEROE ya no estaba simplemente sobreviviendo en territorio enemigo..."
		"\nestaba abriendose paso a traves de el"

		"\n\nSin embargo, mientras observaba el campo de guerra que quedaba atras, resultaba imposible ignorar una idea inquietante"
		"\ncada victoria lo acercaba mas al corazon del reino demoniaco, pero tambien a enemigos cada vez mas peligrosos"

		"\n\nSin detenerse demasiado, el HEROE siguio adelante"
		"\nTodavia quedaba un general mas... y despues de el, el propio Rey Demonio.\n";

	TextoOmitible(mensajePostGeneral2, 75);
	PresionaParaContinuar();
	system("cls");

	// Zona de descanso despues del segundo combate.
	juego.zonaDescanso();

	system("cls");

	PlaySound(TEXT(""), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	// AUN POR MEJORAR
	std::string textoIntermedio3 =
		"Continuando la aventura...."
		"\nla derrota de Karg' Aalh sacudio profundamente a las fuerzas demoniacas"

		"\n\npor primera vez, el HEROE ya no parecia solo un intruso afortunado o un simple guerrero obstinado"
		"\nsu nombre comenzaba a abrirse paso entre los demonios como el de una amenaza real"

		"\n\ndespues de abandonar los campamentos, el camino se volvio mas oscuro y silencioso"
		"\nlas grandes fortalezas y los campos de guerra quedaron atras, dando paso a senderos estrechos"
		"\nbosques consumidos por una niebla espesa y ruinas antiguas donde el peligro parecia esconderse en cada sombra"

		"\n\nlos enfrentamientos continuaban, pero ahora eran distintos"
		"\nlos demonios que aparecian en su camino no atacaban por simple brutalidad ni por deseo de aplastarlo en numero"
		"\nemboscaban"
		"\nobservaban"
		"\nesperaban el momento mas conveniente"

		"\n\nel HEROE siguio adelante, derrotando uno tras otro a todos los enemigos que se interponian en su avance"
		"\ncada vez con mayor determinacion"
		"\nsin darse cuenta, su propio paso se estaba volviendo mas despiadado, como si la guerra misma lo estuviera endureciendo"

		"\n\nal final de aquel trayecto, una tercera fortaleza aparecio ante el HEROE"
		"\na diferencia de las anteriores, esta parecia tener una inquietante sensacion de que todo en aquel lugar lo observaba"

		"\n\nentonces, una voz elegante y serena surgio de entre las sombras\n\n";

	TextoOmitible(textoIntermedio3, 75);
	PresionaParaContinuar();

	PlaySound(NULL, 0, 0);
	system("cls");

	PlaySound(TEXT(""), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	std::string presentacionGeneral3 =
		"Desde la oscuridad emergio una figura alta y delgada"
		"\nde porte impecable y movimientos tan ligeros que parecian deslizarse mas que caminar"

		"\n\nsu sola presencia era distinta a la de los otros generales"
		"\nno habia burlas exageradas ni ansia por pelear, solo una calma refinada y una mirada afilada"

		"\n\nsus ojos observaron al HEROE con una mezcla de estudio, juicio y desden contenido"

		"\n\n- \"Asi que tu eres el humano que ha dejado tras de si un rastro tan inconveniente.....\""

		"\n\nla demonio inclino apenas la cabeza, manteniendo una expresion cortes y fria"

		"\n\n- \"Debo admitir que superar a Karg' Aalh no es una hazania menor,"
		"\naunque superar a Venedictuz creo que incluso nos hiciste un favor a nosotros, pero"
		"\naun asi para alguien de la superficie, has resultado ser una molestia mas grande de lo esperado.\""

		"\n\ndio unos pasos lentos alrededor del HEROE, como si lo analizara con la misma precision"
		"\ncon la que un depredador ve a su presa antes de atacar"

		"\n\n- \"Mi nombre es Zhimingde. y si has llegado hasta aqui, entonces ya no eres una simple molestia... eres una amenaza\""

		"\n\nsu tono siguio siendo elegante, casi amable, pero cada palabra estaba cargada de una frialdad afilada"

		"\n\n- \"Una amenaza para el orden que su majestad sostiene, una amenaza para todo el reino demoniaco y sus planes\""

		"\n\npor fin se detuvo frente al HEROE, clavando en el una mirada tan serena como letal"

		"\n\n- \"Has destruido demasiado, HEROE"
		"\ny por eso, por el bien de mi rey y de nuestro pueblo..."
		"\ntu historia debe terminar aqui.\"\n\n";

	TextoOmitible(presentacionGeneral3, 75);
	PresionaParaContinuar();

	PlaySound(NULL, 0, 0);
	system("cls");

	// Comienza la musica del tercer jefe.
	PlaySound(TEXT("Grimm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	// Tercer combate.
	// Si pierde, se muestra derrota y termina el programa.
	if (!juego.combate(general3)) {
		PlaySound(NULL, 0, 0);
		PlaySound(TEXT("Derrota.wav"), NULL, SND_FILENAME | SND_ASYNC);
		juego.verificarFinal();
		_getch();
		return 0;
	}

	PlaySound(NULL, 0, 0);
	PlaySound(TEXT("Victoria del FINAL.wav"), NULL, SND_FILENAME | SND_ASYNC);

	std::cout << "\n\n---HISTORIA---" << std::endl;
	std::string mensajePostGeneral3 =
		"\nZhimingde cayo, y con ella desaparecio la ultima barrera que separaba al HEROE del castillo del Rey Demonio"

		"\n\nNo hubo celebracion, ni alivio verdadero"
		"\nSolo el silencio de quien comprende que el final del viaje esta al alcance de la mano"

		"\n\nTres generales habian sido derrotados"
		"\nIncontables demonios habian caido en el camino"
		"\nY aun asi, cuanto mas cerca parecia estar la victoria, mas pesada se volvia la sombra de aquella guerra"

		"\n\nEl ultimo campamento aguardaba antes del desenlace"
		"\nDespues de eso, ya no habria mas descanso..."
		"\nsolo el encuentro inevitable con El Rey Demonio.\n";

	TextoOmitible(mensajePostGeneral3, 75);
	PresionaParaContinuar();
	system("cls");

	// Zona de descanso antes del combate final.
	juego.zonaDescanso();

	system("cls");

	PlaySound(TEXT(""), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	// AUN POR MEJORAR
	std::string textoIntermedio4 =
		"Continuando la aventura...."
		"\ncon la caida de Zhimingde, el camino hacia el castillo del Rey Demonio quedo finalmente abierto"

		"\n\nsin embargo, lo que aguardaba mas alla no se parecia a nada de lo que el HEROE hubiera visto antes"
		"\nya no habia necesidad de grandes ejercitos custodiando el paso, ni generales aguardando tras murallas"
		"\nel propio territorio parecia haberse rendido al silencio"
		"\ncomo si todo el reino demoniaco contuviera la respiracion ante el desenlace que se aproximaba"

		"\n\nel HEROE avanzo por caminos oscuros, atravesando restos de fortalezas,"
		"\ntemplos derruidos y ciudades consumidas por la guerra"
		"\naun en ese ultimo tramo, cualquier demonio que estuviera cerca ya lo reconocian como el asesino de demonios"
		"\npor ende no intentaban pararlo porque sabian que era poderoso y peligroso, aun asi habia otros que intentaban pararlo"
		"\na su mala suertee pero aunque alguno se atreviera a interponerse era derribado sin ninguna dificultad"
		"\npara el HEROE ya no eran mas que obstaculos en el camino hacia su destino"

		"\n\nsin embargo, mientras mas se acercaba al castillo final, una sensacion extrania comenzaba a crecer"
		"\nno era miedo"
		"\nno era duda"
		"\nera la pesada certeza de que, al final de aquel trayecto, no solo le esperaba el enemigo mas poderoso de todos..."
		"\nsino el desenlace de aquella guerra"

		"\n\nfinalmente, las puertas del castillo del Rey Demonio se alzaron ante el HEROE"
		"\nen su interior no habia gritos, ni caos, ni burlas"
		"\nsolo un silencio solemne, digno de un trono"

		"\n\ny sentado frente a la inmensidad del salon, aguardaba por fin el rey de los demonios...\n\n";

	TextoOmitible(textoIntermedio4, 75);
	PresionaParaContinuar();

	PlaySound(NULL, 0, 0);
	system("cls");

	PlaySound(TEXT(""), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	std::string presentacionReyDemonio =
		"Sobre un trono oscuro, tallado con una elegancia antigua y sombria, descansaba la figura del Rey Demonio"

		"\n\nEl Rey Demonio no se parecia a los monstruos salvajes ni a las bestias grotescas que el HEROE habia ido dejando atras"
		"\nsu sola presencia imponia una autoridad distinta : la de un verdadero monarca"

		"\n\nde porte impecable, mirada serena y voz profunda, El Rey Demonio observo al HEROE sin rastro de desesperacion,"
		"\nni siquiera despues de haber perdido a sus tres generales y a varios de sus subditos"

		"\n\n- \"Asi que al final has llegado hasta aqui.....\""

		"\n\nsu tono no contenia miedo ni odio"
		"\nsolo una calma pesada, la calma de alguien que ya habia contemplado incontables posibilidades antes de aquel momento"

		"\n\n- \"Has atravesado fortalezas, has destruido ejercitos, has derribado a mis generales..."
		"\ny has segado la vida de innumerables demonios en tu avance\""

		"\n\nEl Rey Demonio se puso de pie lentamente, descendiendo un escalon de su trono sin apartar la vista del HEROE"

		"\n\n- \"Seguramente has venido convencido de que esta es una historia sencilla"
		"\nlos humanos como las victimas"
		"\nlos demonios como los invasores y destructores de su hogar"
		"\nY tu como el heroe destinado a salvarlos todos\""

		"\n\ndurante unos segundos, el Rey Demonio guardo silencio, como si midiera el peso de las palabras que estaba a punto de pronunciar y suspiro"

		"\n\n- \"Pero esta guerra no comenzo por simple ambicion"
		"\nni por hambre de conquista"
		"\nni por un deseo vacio de destruccion\""

		"\n\nsu mirada se ensombrecio levemente"

		"\n\n- \"Desde hace generaciones, en lo profundo de nuestro reino se transmitio una antigua leyenda..."
		"\nla profecia de que un dia un ser de inigualable poder surgiria desde la superficie"
		"\nun ser que arrasaria todo a su paso sin piedad y descenderia hacia el abismo, condenando a mi pueblo a la aniquilacion total\""

		"\n\nEl Rey avanzo unos pasos mas, manteniendo aquella calma casi inquebrantable"

		"\n\n- \"Mientras los humanos vivian en paz en la superficie, nosotros viviamos con la sombra constante de esa extincion sobre nuestras cabezas"
		"\ny cuando porfin me converti en Rey, tome una decision\""

		"\n\nsu voz no se elevo, pero se volvio mas firme"

		"\n\n- \"Invadi la superficie"
		"\nno por crueldad"
		"\nno por placer"
		"\nsino para destruir la amenaza que un dia destruiria a los mios"
		"\ny romper las cadenas de miedo de mi pueblo, trayendo finalmente la paz a mi Reino\""

		"\n\nel Rey Demonio extendio ligeramente una mano, como si con ese gesto abarcara toda la guerra que habia consumido ambos mundos"

		"\n\n- \"Cada uno de mis generales cumplio un papel para sostener ese plan"
		"\nVenedictuz Decimuz mantuvo el control sobre los territorios sometidos y contuvo cualquier resistencia que pudiera desviar nuestra atencion"
		"\nKarg' Aalh arrazo y conquisto, para eliminar cualquier amenza que se alzara contra nosotros"
		"\nZhimingde observo, analizo y planeo, buscando con precision el rastro de aquello que traeria el fin a nuestra raza\""

		"\n\nentonces su mirada se clavo aun mas sobre el HEROE"

		"\n\n- \"Y sin embargo... llegaste tu\""

		"\n\nEl Rey cerro lentamente la mano, como si apretara toda la frustracion de una guerra que se escapaba de su control"

		"\n\n- \"Destruiste mis defensas"
		"\nmataste a incontables de mis subditos"
		"\nderribaste a aquellos que sostenian el destino de mi reino\""

		"\n\nsu tono seguia siendo sereno, pero ahora se podia percibir claramente el peso de su determinacion"

		"\n\n- \"Tu HEROE parece ser la amenaza de la que las leyendas hablaban"
		"\npor eso sin mas opcion tendre que eliminarte aqui, para que mi reino porfin conozca lo que es la paz\""

		"\n\npor primera vez, El Rey adopto una postura de combate, sin perder un solo instante esa dignidad de rey que lo rodeaba"

		"\n\n- \"Si he de cargar con el odio del mundo para proteger a mi pueblo, lo hare"
		"\nSi he de convertirme en el monstruo de tu historia para salvar el abismo, lo aceptare\""

		"\n\nfinalmente, sus ojos se endurecieron"

		"\n\n- \"Aqui termina todo, HEROE"
		"\ndemuestrame si tu voluntad es mas fuerte que la desesperacion de un rey..."
		"\no perece aqui..., ante Abyssandros, soberano del abismo\"\n\n";

	TextoOmitible(presentacionReyDemonio, 75);
	PresionaParaContinuar();

	PlaySound(NULL, 0, 0);
	system("cls");

	// Comienza la musica del jefe final.
	PlaySound(TEXT("Bloody Tears.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	// Combate final contra el Rey Demonio.
	// Si pierde, se muestra derrota y termina el programa.
	if (!juego.combate(reyDemonio)) {
		PlaySound(NULL, 0, 0);
		PlaySound(TEXT("Derrota.wav"), NULL, SND_FILENAME | SND_ASYNC);
		juego.verificarFinal();
		_getch();
		return 0;
	}

	PlaySound(NULL, 0, 0);
	PlaySound(TEXT("Victoria del FINAL.wav"), NULL, SND_FILENAME | SND_ASYNC);

	// Si llega hasta aqui, se muestra el final correspondiente.
	juego.verificarFinal();

	PresionaParaContinuar();
	return 0;
}