<div class="tagidsUsers view">
<h2><?php echo __('Tagids User'); ?></h2>
	<dl>
		<dt><?php echo __('Id'); ?></dt>
		<dd>
			<?php echo h($tagidsUser['TagidsUser']['id']); ?>
			&nbsp;
		</dd>
		<dt><?php echo __('Tagid'); ?></dt>
		<dd>
			<?php echo $this->Html->link($tagidsUser['Tagid']['id'], array('controller' => 'tagids', 'action' => 'view', $tagidsUser['Tagid']['id'])); ?>
			&nbsp;
		</dd>
		<dt><?php echo __('User'); ?></dt>
		<dd>
			<?php echo $this->Html->link($tagidsUser['User']['id'], array('controller' => 'users', 'action' => 'view', $tagidsUser['User']['id'])); ?>
			&nbsp;
		</dd>
		<dt><?php echo __('Created'); ?></dt>
		<dd>
			<?php echo h($tagidsUser['TagidsUser']['created']); ?>
			&nbsp;
		</dd>
		<dt><?php echo __('Modified'); ?></dt>
		<dd>
			<?php echo h($tagidsUser['TagidsUser']['modified']); ?>
			&nbsp;
		</dd>
	</dl>
</div>
<div class="actions">
	<h3><?php echo __('Actions'); ?></h3>
	<ul>
		<li><?php echo $this->Html->link(__('Menu Principal'), array('controller' => 'pages' ,'action' => 'index')); ?></li>
		<li><?php echo $this->Html->link(__('Editar Associação'), array('action' => 'edit', $tagidsUser['TagidsUser']['id'])); ?> </li>
		<li><?php echo $this->Form->postLink(__('Deletar Associação'), array('action' => 'delete', $tagidsUser['TagidsUser']['id']), array(), __('Are you sure you want to delete # %s?', $tagidsUser['TagidsUser']['id'])); ?> </li>
		<li><?php echo $this->Html->link(__('Listar Usuários/Tag'), array('action' => 'index')); ?> </li>
	</ul>
</div>
