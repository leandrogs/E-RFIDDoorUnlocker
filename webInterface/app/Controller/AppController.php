<?php
/**
 * Application level Controller
 *
 * This file is application-wide controller file. You can put all
 * application-wide controller-related methods here.
 *
 * CakePHP(tm) : Rapid Development Framework (http://cakephp.org)
 * Copyright (c) Cake Software Foundation, Inc. (http://cakefoundation.org)
 *
 * Licensed under The MIT License
 * For full copyright and license information, please see the LICENSE.txt
 * Redistributions of files must retain the above copyright notice.
 *
 * @copyright     Copyright (c) Cake Software Foundation, Inc. (http://cakefoundation.org)
 * @link          http://cakephp.org CakePHP(tm) Project
 * @package       app.Controller
 * @since         CakePHP(tm) v 0.2.9
 * @license       http://www.opensource.org/licenses/mit-license.php MIT License
 */

App::uses('Controller', 'Controller');

/**
 * Application Controller
 *
 * Add your application-wide methods in the class below, your controllers
 * will inherit them.
 *
 * @package		app.Controller
 * @link		http://book.cakephp.org/2.0/en/controllers.html#the-app-controller
 */
class AppController extends Controller {

	//Define os componentes da Session corrente
	//Autorização realizada nos controllers
	//Sempre redireciona para a página principal em caso de login ou logout
	public $components = array(
		'Session',
		'Auth' => array(
			'loginRedirect' => array('controller' => 'pages', 'action' => 'index'),
			'logoutRedirect' => array('controller' => 'pages', 'action' => 'index'),
			'authError' => 'You can´t access that page',
			'authorize' => array('Controller')
		)
	);

	//Define autorizacao geral para um usuario que se loga
	//Libera acesso total ao sistema para um usuario com nível administrador
	//Bloquea acesso total ao sistema para um usuario com nível regular
	//Para um usuario com nivel regular os desbloqueo de views sao feitas nos
	//respectivos controllers
	public function isAuthorized($user){

		if($user['role'] == 'admin'){

      		return true;
   		}

   		return false;
	}
}
