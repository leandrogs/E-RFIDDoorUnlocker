<?php
App::uses('AppController', 'Controller');
/**
 * Tagids Controller
 *
 * @property Tagid $Tagid
 * @property PaginatorComponent $Paginator
 */
class TagidsController extends AppController {

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
		$this->Tagid->recursive = 0;
		$this->set('tagids', $this->Paginator->paginate());
	}

/**
 * view method
 *
 * @throws NotFoundException
 * @param string $id
 * @return void
 */
	public function view($id = null) {
		if (!$this->Tagid->exists($id)) {
			throw new NotFoundException(__('Invalid tagid'));
		}
		$options = array('conditions' => array('Tagid.' . $this->Tagid->primaryKey => $id));
		$this->set('tagid', $this->Tagid->find('first', $options));
	}

/**
 * add method
 *
 * @return void
 */
	public function add() {
		if ($this->request->is('post')) {
			$this->Tagid->create();
			if ($this->Tagid->save($this->request->data)) {
				$this->Session->setFlash(__('The tagid has been saved.'));
				return $this->redirect(array('action' => 'index'));
			} else {
				$this->Session->setFlash(__('The tagid could not be saved. Please, try again.'));
			}
		}
		$users = $this->Tagid->User->find('list');
		$this->set(compact('users'));
	}

/**
 * edit method
 *
 * @throws NotFoundException
 * @param string $id
 * @return void
 */
	public function edit($id = null) {
		if (!$this->Tagid->exists($id)) {
			throw new NotFoundException(__('Invalid tagid'));
		}
		if ($this->request->is(array('post', 'put'))) {
			if ($this->Tagid->save($this->request->data)) {
				$this->Session->setFlash(__('The tagid has been saved.'));
				return $this->redirect(array('action' => 'index'));
			} else {
				$this->Session->setFlash(__('The tagid could not be saved. Please, try again.'));
			}
		} else {
			$options = array('conditions' => array('Tagid.' . $this->Tagid->primaryKey => $id));
			$this->request->data = $this->Tagid->find('first', $options);
		}
		$users = $this->Tagid->User->find('list');
		$this->set(compact('users'));
	}

/**
 * delete method
 *
 * @throws NotFoundException
 * @param string $id
 * @return void
 */
	public function delete($id = null) {
		$this->Tagid->id = $id;
		if (!$this->Tagid->exists()) {
			throw new NotFoundException(__('Invalid tagid'));
		}
		$this->request->allowMethod('post', 'delete');
		if ($this->Tagid->delete()) {
			$this->Session->setFlash(__('The tagid has been deleted.'));
		} else {
			$this->Session->setFlash(__('The tagid could not be deleted. Please, try again.'));
		}
		return $this->redirect(array('action' => 'index'));
	}
}
