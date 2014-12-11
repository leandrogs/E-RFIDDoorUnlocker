<?php
App::uses('AppController', 'Controller');
/**
 * TagidsUsers Controller
 *
 * @property TagidsUser $TagidsUser
 * @property PaginatorComponent $Paginator
 */
class TagidsUsersController extends AppController {

/**
 * Components
 *
 * @var array
 */
	public $components = array('Paginator');

/**
 * index method
 *
 * @return void
 */
	public function index() {
		$this->TagidsUser->recursive = 0;
		$this->set('tagidsUsers', $this->Paginator->paginate());
	}

/**
 * view method
 *
 * @throws NotFoundException
 * @param string $id
 * @return void
 */
	public function view($id = null) {
		if (!$this->TagidsUser->exists($id)) {
			throw new NotFoundException(__('Invalid tagids user'));
		}
		$options = array('conditions' => array('TagidsUser.' . $this->TagidsUser->primaryKey => $id));
		$this->set('tagidsUser', $this->TagidsUser->find('first', $options));
	}

/**
 * add method
 *
 * @return void
 */
	public function add() {
		if ($this->request->is('post')) {

			// debug($this->request->data) or die();
			$this->TagidsUser->create();
			if ($this->TagidsUser->save($this->request->data)) {
				$this->Session->setFlash(__('The tagids user has been saved.'));
				return $this->redirect(array('action' => 'index'));
			} else {
				$this->Session->setFlash(__('The tagids user could not be saved. Please, try again.'));
			}
		}
		$tagids = $this->TagidsUser->Tagid->find('list', array('recursive' => -1,
															  'fields' => array('Tagid.id', 'Tagid.tagid') ));
		$users = $this->TagidsUser->User->find('list', array('recursive' => -1,
															  'fields' => array('User.id', 'User.username') ));
		$this->set(compact('tagids', 'users'));
	}

/**
 * edit method
 *
 * @throws NotFoundException
 * @param string $id
 * @return void
 */
	public function edit($id = null) {
		if (!$this->TagidsUser->exists($id)) {
			throw new NotFoundException(__('Invalid tagids user'));
		}
		if ($this->request->is(array('post', 'put'))) {
			if ($this->TagidsUser->save($this->request->data)) {
				$this->Session->setFlash(__('The tagids user has been saved.'));
				return $this->redirect(array('action' => 'index'));
			} else {
				$this->Session->setFlash(__('The tagids user could not be saved. Please, try again.'));
			}
		} else {
			$options = array('conditions' => array('TagidsUser.' . $this->TagidsUser->primaryKey => $id));
			$this->request->data = $this->TagidsUser->find('first', $options);
		}
		$tagids = $this->TagidsUser->Tagid->find('list');
		$users = $this->TagidsUser->User->find('list');
		$this->set(compact('tagids', 'users'));
	}

/**
 * delete method
 *
 * @throws NotFoundException
 * @param string $id
 * @return void
 */
	public function delete($id = null) {
		$this->TagidsUser->id = $id;
		if (!$this->TagidsUser->exists()) {
			throw new NotFoundException(__('Invalid tagids user'));
		}
		$this->request->allowMethod('post', 'delete');
		if ($this->TagidsUser->delete()) {
			$this->Session->setFlash(__('The tagids user has been deleted.'));
		} else {
			$this->Session->setFlash(__('The tagids user could not be deleted. Please, try again.'));
		}
		return $this->redirect(array('action' => 'index'));
	}
}
