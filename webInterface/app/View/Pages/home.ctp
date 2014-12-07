<div class="actions">
	<h3><?php echo __('Actions'); ?></h3>
	<ul>

		<li><?php echo $this->Html->link(__('Listar Usuários'), array('controller' => 'users' ,'action' => 'index')); ?></li>
		<li><?php echo $this->Html->link(__('Adicionar Usuário'), array('controller' => 'users' ,'action' => 'add')); ?></li>
		<li><?php echo $this->Html->link(__('Listar Tags'), array('controller' => 'tagids', 'action' => 'index')); ?> </li>
		<li><?php echo $this->Html->link(__('Listar Usuários/Tags'), array('controller' => 'tagidsusers' ,'action' => 'index')); ?></li>
		<li><?php echo $this->Html->link(__('Associar Usuários/Tag'), array('controller' => 'tagidsusers' ,'action' => 'add')); ?></li>

	</ul>
</div>